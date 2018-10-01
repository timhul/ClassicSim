
#include "EncounterEnd.h"
#include "Character.h"

EncounterEnd::EncounterEnd(Engine* engine, Character* pchar) {
    this->engine = engine;
    this->pchar = pchar;
    this->priority = 300.0;
    this->name = "EncounterEnd";
}

void EncounterEnd::act() {
    pchar->reset();
    engine->end_combat();
}
