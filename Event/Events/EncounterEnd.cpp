
#include "EncounterEnd.h"
#include <iostream>

EncounterEnd::EncounterEnd(void) {
    this->priority = 300.0;
}

void EncounterEnd::act(void) {
    std::cout << "EncounterEnd\n";
}
