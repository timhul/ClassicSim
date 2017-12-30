
#include "MainhandMeleeHit.h"

#include <iostream>

MainhandMeleeHit::MainhandMeleeHit(Character* pchar, const float next_timestamp) {
    this->pchar = pchar;
    this->priority = next_timestamp;
}

void MainhandMeleeHit::act(void) {
    std::cout << this->priority << ": MainhandMeleeHit\n";
    pchar->mh_auto_attack();
}
