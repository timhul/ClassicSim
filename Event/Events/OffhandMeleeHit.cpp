
#include "OffhandMeleeHit.h"
#include "Character.h"

#include <iostream>

OffhandMeleeHit::OffhandMeleeHit(Character* pchar, const float next_timestamp) {
    this->pchar = pchar;
    this->priority = next_timestamp;
    this->name = "OffhandMeleeHit";
}

void OffhandMeleeHit::act(void) {
    //std::cout << this->priority << ": OffhandMeleeHit\n";
    pchar->oh_auto_attack();
}
