
#include "OffhandMeleeHit.h"
#include "Character.h"

OffhandMeleeHit::OffhandMeleeHit(Character* pchar, const float next_timestamp, const int iteration) {
    this->pchar = pchar;
    this->priority = next_timestamp;
    this->name = "OffhandMeleeHit";
    this->iteration = iteration;
}

void OffhandMeleeHit::act(void) {
    pchar->oh_auto_attack(iteration);
}
