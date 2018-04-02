
#include "Engine.h"
#include <QDebug>

void Engine::run() {
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
    statistics->clear();
    processed_events_of_type.clear();
}

void Engine::dump(void) {
    const float elapsed = (float)timer->elapsed() / 1000;
    statistics->dump();

    QMap<QString, int>::const_iterator i = processed_events_of_type.constBegin();
    while (i != processed_events_of_type.constEnd()) {
        qDebug() << i.key() << "=>" << i.value() << (float(i.value()) / float(processed_events)) * 100 << "%";
        ++i;
    }

    qDebug() << "Processed" << processed_events << "events in " << elapsed << "s";
    qDebug() << processed_events / elapsed << " events per second";
}

void Engine::reset(void) {
    current_prio = -1;
    processed_events = 0;
    delete timer;
    timer = new QTime();
}

void Engine::end_combat(void) {   
    queue->clear();
    current_prio = -1;
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
    this->queue->push(event);
}

Statistics* Engine::get_statistics(void) {
    return this->statistics;
}

void Engine::save_event_history(Event* event) {
    if (!processed_events_of_type.contains(event->get_name()))
        processed_events_of_type[event->get_name()] = 0;

    processed_events_of_type[event->get_name()]++;
}
