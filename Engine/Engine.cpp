#include "Engine.h"

#include "Event.h"
#include "Queue.h"
#include "StatisticsEngine.h"
#include "Utils/Check.h"

Engine::Engine() : queue(new Queue()), timer(new QElapsedTimer()), current_prio(0) {}

Engine::~Engine() {
    delete queue;
    delete timer;
}

void Engine::run() {
    while (!queue->empty()) {
        Event* event = queue->get_next();
        set_current_priority(event);
        engine_statistics->increment_event(event->event_type);
        event->act();
        delete event;
    }
}

void Engine::prepare_set_of_iterations(StatisticsEngine* engine_statistics) {
    this->engine_statistics = engine_statistics;
    current_prio = 0;
    queue->clear();
    timer->start();
}

void Engine::prepare_iteration(const double start_at) {
    queue->clear();
    current_prio = start_at;
}

void Engine::reset() {
    engine_statistics->set_elapsed(static_cast<unsigned>(timer->elapsed()));
    delete timer;
    timer = new QElapsedTimer();
}

void Engine::end_combat() {
    queue->clear();
}

double Engine::get_current_priority() const {
    return current_prio;
}

void Engine::set_current_priority(Event* event) {
    check((event->priority >= this->current_prio),
          QString("Engine is at '%1' and got event at '%2'").arg(current_prio).arg(event->priority).toStdString());
    this->current_prio = event->priority;
}

void Engine::add_event(Event* event) {
    this->queue->push(event);
}

Queue* Engine::get_queue() const {
    return this->queue;
}
