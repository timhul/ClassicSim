#include "MainhandMeleeHit.h"

#include "CharacterSpells.h"

MainhandMeleeHit::MainhandMeleeHit(CharacterSpells* spells, const double next_timestamp, const int iteration):
    Event(Events::MainhandMeleeHit, next_timestamp, "MainhandMeleeHit"),
    spells(spells),
    iteration(iteration)
{}

void MainhandMeleeHit::act() {
    spells->mh_auto_attack(iteration);
}
