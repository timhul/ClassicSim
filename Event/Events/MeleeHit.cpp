
#include "MeleeHit.h"

MeleeHit::MeleeHit(Character* pchar) {
    this->pchar = pchar;
    this->priority = pchar->get_engine()->get_current_priority() + 1;
}

void MeleeHit::act(void) {
    pchar->auto_attack();
    // TODO: Add next auto attack based on weapon speed.
}
