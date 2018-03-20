
#include "EncounterEnd.h"
#include <iostream>

EncounterEnd::EncounterEnd(Engine* engine) {
    this->engine = engine;
    this->priority = 300.0;
    this->name = "EncounterEnd";
}

void EncounterEnd::act(void) {
    std::cout << this->priority << ": EncounterEnd\n";
    engine->end_combat();
}
