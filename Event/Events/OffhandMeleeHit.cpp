
#include "OffhandMeleeHit.h"
#include "Character.h"

OffhandMeleeHit::OffhandMeleeHit(Character* pchar, const float next_timestamp) {
    this->pchar = pchar;
    this->priority = next_timestamp;
    this->name = "OffhandMeleeHit";
}

void OffhandMeleeHit::act(void) {
    pchar->oh_auto_attack();
}
