
#include "MeleeHit.h"
#include <iostream>

MeleeHit::MeleeHit(Character* pchar) {
    this->pchar = pchar;
    this->priority = pchar->get_engine()->get_current_priority() + 1;
}

void MeleeHit::act(void) {
    std::cout << "MeleeHit\n";
}
