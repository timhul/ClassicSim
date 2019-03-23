#include "EncounterStart.h"

#include "CharacterSpells.h"

EncounterStart::EncounterStart(CharacterSpells* spells) {
    this->spells = spells;
    this->priority = 0.0;
    this->name = "EncounterStart";
}

void EncounterStart::act() {
    spells->run_pre_combat_spells();
    spells->start_attack();
    spells->perform_rotation();
}
