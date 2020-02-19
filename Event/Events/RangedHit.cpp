#include "RangedHit.h"

#include "CharacterSpells.h"

RangedHit::RangedHit(CharacterSpells* spells, const double next_timestamp, const int iteration) :
    Event(EventType::RangedHit, next_timestamp), spells(spells), iteration(iteration) {}

void RangedHit::act() {
    spells->ranged_auto_attack(iteration);
}
