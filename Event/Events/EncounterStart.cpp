#include "EncounterStart.h"

#include "CharacterSpells.h"
#include "EnabledBuffs.h"

EncounterStart::EncounterStart(CharacterSpells* spells, EnabledBuffs* buffs):
    Event(Events::EncounterStart)
{
    this->spells = spells;
    this->buffs = buffs;
    this->priority = 0.0;
    this->name = "EncounterStart";
}

void EncounterStart::act() {
    buffs->apply_start_of_combat_buffs();
    spells->run_start_of_combat_spells();
    spells->start_attack();
    spells->start_pet_attack();
    spells->perform_rotation();
}
