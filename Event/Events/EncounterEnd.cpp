#include "EncounterEnd.h"

#include "Character.h"
#include "Engine.h"

EncounterEnd::EncounterEnd(Engine* engine, const int combat_length):
    Event(EventType::EncounterEnd, static_cast<double>(combat_length)),
    engine(engine)
{}

void EncounterEnd::act() {
    engine->end_combat();
}
