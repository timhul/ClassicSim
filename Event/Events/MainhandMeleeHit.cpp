#include "MainhandMeleeHit.h"

#include "CharacterSpells.h"

MainhandMeleeHit::MainhandMeleeHit(CharacterSpells* spells, const double next_timestamp, const int iteration):
    Event(Events::MainhandMeleeHit)
{
    this->spells = spells;
    this->priority = next_timestamp;
    this->name = "MainhandMeleeHit";
    this->iteration = iteration;
}

void MainhandMeleeHit::act() {
    spells->mh_auto_attack(iteration);
}
