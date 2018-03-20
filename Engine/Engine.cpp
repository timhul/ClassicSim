
#include "Engine.h"
#include <QDebug>

void Engine::run(void) {
    while(!queue->empty()) {
        Event* event = queue->get_next();
        qDebug() << event->get_priority() << ": Running " << event->get_name();
        set_current_priority(event);
        event->act();
        delete event;
    }
    statistics->dump();
}

void Engine::end_combat(void) {
    qDebug() << "Engine: Ending combat.";
    queue->clear();
}

float Engine::get_current_priority(void) const {
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
    qDebug() << current_prio << ": " << event->get_name() << " event added with priority " << event->get_priority();
    this->queue->push(event);
}

Statistics* Engine::get_statistics(void) {
    return this->statistics;
}
