
#include "Engine.h"
#include "EncounterStart.h"
#include "EncounterEnd.h"
#include "Human.h"

#include <iostream>

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

void Engine::test_character_creation(void) {
    Race* race = new Human();
    std::cout << "Name: " << race->get_name() << "\n";
    std::cout << "STR " << race->get_base_strength() << "\n";
    std::cout << "AGI " << race->get_base_agility() << "\n";
    std::cout << "STA " << race->get_base_stamina() << "\n";
    std::cout << "INT " << race->get_base_intellect() << "\n";
    std::cout << "SPI " << race->get_base_spirit() << "\n";
}
