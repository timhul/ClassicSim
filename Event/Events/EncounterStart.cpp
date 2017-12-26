
#include "EncounterStart.h"
#include <iostream>

EncounterStart::EncounterStart(void) {
    this->priority = 0.0;
}

void EncounterStart::act(void) {
    std::cout << "EncounterStart\n";
}
