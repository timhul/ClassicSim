
#include "EncounterStart.h"
#include <iostream>

EncounterStart::EncounterStart(Character* pchar) {
    this->pchar = pchar;
    this->priority = 0.0;
}

void EncounterStart::act(void) {
    std::cout << this->priority << ": EncounterStart\n";
    pchar->rotation();
}
