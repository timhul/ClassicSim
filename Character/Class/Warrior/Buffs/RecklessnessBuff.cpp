
#include "RecklessnessBuff.h"
#include "Warrior.h"
#include "CharacterStats.h"

RecklessnessBuff::RecklessnessBuff(Character* pchar):
    Buff(pchar, "Recklessness", "Assets/warrior/Ability_criticalstrike.png", 15, 0)
{}

void RecklessnessBuff::buff_effect_when_applied() {
    dynamic_cast<Warrior*>(pchar)->get_stats()->increase_crit(1.0);
}

void RecklessnessBuff::buff_effect_when_removed() {
    dynamic_cast<Warrior*>(pchar)->get_stats()->decrease_crit(1.0);
}
