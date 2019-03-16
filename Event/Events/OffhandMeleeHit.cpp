#include "OffhandMeleeHit.h"

#include "CharacterSpells.h"

OffhandMeleeHit::OffhandMeleeHit(CharacterSpells* spells, const double next_timestamp, const int iteration) {
    this->spells = spells;
    this->priority = next_timestamp;
    this->name = "OffhandMeleeHit";
    this->iteration = iteration;
}

void OffhandMeleeHit::act() {
    spells->oh_auto_attack(iteration);
}
