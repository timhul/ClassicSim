
#include "EncounterEnd.h"
#include "Character.h"

EncounterEnd::EncounterEnd(Engine* engine, Character* pchar, int combat_length) {
    this->engine = engine;
    this->pchar = pchar;
    this->priority = double(combat_length);
    this->name = "EncounterEnd";
}

void EncounterEnd::act() {
    pchar->reset();
    engine->end_combat();
}
