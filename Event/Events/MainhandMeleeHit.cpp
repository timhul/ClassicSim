#include "MainhandMeleeHit.h"

#include "CharacterSpells.h"

MainhandMeleeHit::MainhandMeleeHit(CharacterSpells* spells, const double next_timestamp, const int iteration):
    Event(EventType::MainhandMeleeHit, next_timestamp),
    spells(spells),
    iteration(iteration)
{}

void MainhandMeleeHit::act() {
    spells->mh_auto_attack(iteration);
}
