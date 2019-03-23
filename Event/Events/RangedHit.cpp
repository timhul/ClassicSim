#include "RangedHit.h"

#include "CharacterSpells.h"

RangedHit::RangedHit(CharacterSpells* spells, const double next_timestamp, const int iteration) {
    this->spells = spells;
    this->priority = next_timestamp;
    this->name = "RangedHit";
    this->iteration = iteration;
}

void RangedHit::act() {
    spells->ranged_auto_attack(iteration);
}
