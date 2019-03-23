#include "EncounterEnd.h"

#include "Character.h"
#include "Engine.h"

EncounterEnd::EncounterEnd(Engine* engine, Character* pchar, int combat_length) {
    this->engine = engine;
    this->pchar = pchar;
    this->priority = static_cast<double>(combat_length);
    this->name = "EncounterEnd";
}

void EncounterEnd::act() {
    pchar->reset();
    engine->end_combat();
}
