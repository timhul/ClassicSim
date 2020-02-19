#include "RecklessnessBuff.h"

#include "CharacterStats.h"
#include "Warrior.h"

RecklessnessBuff::RecklessnessBuff(Character* pchar) : SelfBuff(pchar, "Recklessness", "Assets/ability/Ability_criticalstrike.png", 15, 0) {}

void RecklessnessBuff::buff_effect_when_applied() {
    pchar->get_stats()->increase_melee_aura_crit(999999);
}

void RecklessnessBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_melee_aura_crit(999999);
}
