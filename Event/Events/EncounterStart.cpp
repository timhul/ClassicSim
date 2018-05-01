
#include "EncounterStart.h"
#include "Character.h"
#include "Spells.h"

EncounterStart::EncounterStart(Character* pchar) {
    this->pchar = pchar;
    this->priority = 0.0;
    this->name = "EncounterStart";
}

void EncounterStart::act(void) {
    pchar->rotation();
}
