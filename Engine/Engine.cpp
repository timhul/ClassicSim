
#include "Engine.h"
#include <QDebug>

Engine::Engine():
    queue(new Queue()),
    timer(new QTime()),
    current_prio(0),
    processed_events(0)
{}

Engine::~Engine() {
    delete queue;
    delete timer;
}

void Engine::run() {
    processed_events_of_type.clear();
    while(!queue->empty()) {
        ++processed_events;
        Event* event = queue->get_next();
        set_current_priority(event);
        save_event_history(event);
        event->act();
        delete event;
    }
}

void Engine::prepare() {
    timer->start();
    processed_events_of_type.clear();
}

void Engine::dump() {
    const double elapsed = double(timer->elapsed()) / 1000;

    QMap<QString, int>::const_iterator i = processed_events_of_type.constBegin();
    while (i != processed_events_of_type.constEnd()) {
        qDebug() << i.key() << "=>" << i.value() << (double(i.value()) / double(processed_events)) * 100 << "%";
        ++i;
    }

    qDebug() << "Processed" << processed_events << "events in" << elapsed << "s";
    qDebug() << processed_events / elapsed << "events per second";
}

void Engine::reset() {
    current_prio = -1;
    processed_events = 0;
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
    if (event->get_priority() < this->current_prio) {
        qDebug() << "Engine: Next event lower priority than current prio! " \
                 << event->get_priority() << " < " << this->current_prio;
        exit(-1);
    }
    this->current_prio = event->get_priority();
}

void Engine::add_event(Event* event) {
    this->queue->push(event);
}

Queue* Engine::get_queue() const {
    return this->queue;
}

void Engine::save_event_history(Event* event) {
    if (!processed_events_of_type.contains(event->get_name()))
        processed_events_of_type[event->get_name()] = 0;

    processed_events_of_type[event->get_name()]++;
}
