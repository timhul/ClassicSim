
#include "MainhandMeleeHit.h"
#include "Spells.h"

MainhandMeleeHit::MainhandMeleeHit(Spells* spells, const double next_timestamp, const int iteration) {
    this->spells = spells;
    this->priority = next_timestamp;
    this->name = "MainhandMeleeHit";
    this->iteration = iteration;
}

void MainhandMeleeHit::act(void) {
    spells->mh_auto_attack(iteration);
}
