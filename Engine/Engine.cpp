#include "Engine.h"

#include "Event.h"
#include "Queue.h"
#include "Utils/Check.h"

Engine::Engine():
    queue(new Queue()),
    timer(new QTime()),
    current_prio(0)
{}

Engine::~Engine() {
    delete queue;
    delete timer;
}

void Engine::run() {
    while(!queue->empty()) {
        Event* event = queue->get_next();
        set_current_priority(event);
        event->act();
        delete event;
    }
}

void Engine::prepare() {
    reset();
    timer->start();
}

void Engine::reset() {
    current_prio = -1;
    queue->clear();
    delete timer;
    timer = new QTime();
}

void Engine::end_combat() {
    queue->clear();
    current_prio = -1;
}

double Engine::get_current_priority() const {
    return current_prio;
}

void Engine::set_current_priority(Event* event) {
    check((event->get_priority() >= this->current_prio),
          QString("Engine is at '%1' and got event at '%2'").arg(current_prio).arg(event->get_priority()).toStdString());
    this->current_prio = event->get_priority();
}

void Engine::add_event(Event* event) {
    this->queue->push(event);
}

Queue* Engine::get_queue() const {
    return this->queue;
}
