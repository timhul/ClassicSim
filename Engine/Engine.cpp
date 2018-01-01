
#include "Engine.h"

#include <iostream>

void Engine::run(void) {
    while(!queue->empty()) {
        Event* event = queue->get_next();
        set_current_priority(event);
        event->act();
        delete event;
    }
    statistics->dump();
}

void Engine::end_combat(void) {
    std::cout << "Engine: Ending combat.\n";
    queue->clear();
}

float Engine::get_current_priority(void) const {
    return current_prio;
}

void Engine::set_current_priority(Event* event) {
    if (event->get_priority() < this->current_prio) {
        std::cerr << "Engine: Next event lower priority than current prio! " \
                  << event->get_priority() << " < " << this->current_prio << "\n";
        exit(-1);
    }
    this->current_prio = event->get_priority();
}

void Engine::add_event(Event* event) {
    this->queue->push(event);
}

Statistics* Engine::get_statistics(void) {
    return this->statistics;
}
