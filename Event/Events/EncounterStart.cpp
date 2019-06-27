#include "EncounterStart.h"

#include "CharacterSpells.h"
#include "EnabledBuffs.h"

EncounterStart::EncounterStart(CharacterSpells* spells, EnabledBuffs* buffs):
    Event(Events::EncounterStart, 0.0, "EncounterStart"),
    spells(spells),
    buffs(buffs)
{}

void EncounterStart::act() {
    buffs->apply_start_of_combat_buffs();
    spells->run_start_of_combat_spells();
    spells->start_attack();
    spells->start_pet_attack();
    spells->perform_rotation();
}
