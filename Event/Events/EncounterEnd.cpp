
#include "EncounterEnd.h"

EncounterEnd::EncounterEnd(Engine* engine) {
    this->engine = engine;
    this->priority = 300.0;
    this->name = "EncounterEnd";
}

void EncounterEnd::act(void) {
    engine->end_combat();
}
