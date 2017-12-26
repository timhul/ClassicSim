
#include "Engine.h"
#include "EncounterStart.h"
#include "EncounterEnd.h"

void Engine::run(void) {
    while(!queue.empty()) {
        Event* event = queue.get_next();
        event->act();
        delete event;
    }
}

void Engine::test_queue(void) {
    EncounterStart* start_event = new EncounterStart();
    EncounterEnd* end_event = new EncounterEnd();
    this->queue.push(end_event);
    this->queue.push(start_event);
    run();
}
