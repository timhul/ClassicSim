
#include "MainhandMeleeHit.h"
#include "Character.h"

MainhandMeleeHit::MainhandMeleeHit(Character* pchar, const float next_timestamp, const int iteration) {
    this->pchar = pchar;
    this->priority = next_timestamp;
    this->name = "MainhandMeleeHit";
    this->iteration = iteration;
}

void MainhandMeleeHit::act(void) {
    pchar->mh_auto_attack(iteration);
}
