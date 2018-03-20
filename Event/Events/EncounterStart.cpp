
#include "EncounterStart.h"
#include "Character.h"
#include <iostream>

EncounterStart::EncounterStart(Character* pchar) {
    this->pchar = pchar;
    this->priority = 0.0;
    this->name = "EncounterStart";
}

void EncounterStart::act(void) {
    std::cout << this->priority << ": EncounterStart\n";
    pchar->rotation();
}
