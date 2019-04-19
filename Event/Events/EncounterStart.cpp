#include "EncounterStart.h"

#include "CharacterSpells.h"
#include "EnabledBuffs.h"

EncounterStart::EncounterStart(CharacterSpells* spells, EnabledBuffs* buffs) {
    this->spells = spells;
    this->buffs = buffs;
    this->priority = 0.0;
    this->name = "EncounterStart";
}

void EncounterStart::act() {
    buffs->apply_pre_combat_buffs();
    spells->run_pre_combat_spells();
    spells->start_attack();
    spells->start_pet_attack();
    spells->perform_rotation();
}
