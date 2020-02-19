#include "OffhandMeleeHit.h"

#include "CharacterSpells.h"

OffhandMeleeHit::OffhandMeleeHit(CharacterSpells* spells, const double timestamp, const int iteration) :
    Event(EventType::OffhandMeleeHit, timestamp), spells(spells), iteration(iteration) {}

void OffhandMeleeHit::act() {
    spells->oh_auto_attack(iteration);
}
