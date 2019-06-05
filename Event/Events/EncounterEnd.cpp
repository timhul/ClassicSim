#include "EncounterEnd.h"

#include "Character.h"
#include "Engine.h"

EncounterEnd::EncounterEnd(Engine* engine, int combat_length):
    Event(Events::EncounterEnd)
{
    this->engine = engine;
    this->priority = static_cast<double>(combat_length);
    this->name = "EncounterEnd";
}

void EncounterEnd::act() {
    engine->end_combat();
}
