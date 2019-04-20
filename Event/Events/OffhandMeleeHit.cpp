#include "OffhandMeleeHit.h"

#include "CharacterSpells.h"

OffhandMeleeHit::OffhandMeleeHit(CharacterSpells* spells, const double timestamp, const int iteration):
    Event(Events::OffhandMeleeHit)
{
    this->spells = spells;
    this->priority = timestamp;
    this->name = "OffhandMeleeHit";
    this->iteration = iteration;
}

void OffhandMeleeHit::act() {
    spells->oh_auto_attack(iteration);
}
