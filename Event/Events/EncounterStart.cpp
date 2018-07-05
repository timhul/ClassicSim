
#include "EncounterStart.h"
#include "Character.h"
#include "Spells.h"

EncounterStart::EncounterStart(Character* pchar) {
    this->pchar = pchar;
    this->priority = 0.0;
    this->name = "EncounterStart";
}

void EncounterStart::act(void) {
    // TODO: Make start_attack() virtual such that ranged classes do not start melee attacking.
    pchar->start_attack();
    pchar->perform_rotation();
}
