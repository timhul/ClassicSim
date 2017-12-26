
#include "EncounterStart.h"
#include <iostream>

EncounterStart::EncounterStart(Character* pchar) {
    this->pchar = pchar;
    this->priority = 0.0;
}

void EncounterStart::act(void) {
    std::cout << "EncounterStart\n";
    pchar->let_player_act();
}
