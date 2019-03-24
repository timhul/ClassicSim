#include "RecklessnessBuff.h"

#include "CharacterStats.h"
#include "Warrior.h"

RecklessnessBuff::RecklessnessBuff(Character* pchar):
    Buff(pchar, "Recklessness", "Assets/ability/Ability_criticalstrike.png", 15, 0)
{}

void RecklessnessBuff::buff_effect_when_applied() {
    dynamic_cast<Warrior*>(pchar)->get_stats()->increase_melee_crit(10000);
}

void RecklessnessBuff::buff_effect_when_removed() {
    dynamic_cast<Warrior*>(pchar)->get_stats()->decrease_melee_crit(10000);
}
