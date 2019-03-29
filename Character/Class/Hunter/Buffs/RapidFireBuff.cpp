#include "RapidFireBuff.h"

#include "CharacterStats.h"
#include "Hunter.h"

RapidFireBuff::RapidFireBuff(Character* pchar):
    Buff(pchar, "Rapid Fire", "Assets/ability/Ability_hunter_runningshot.png", 15, 0)
{}

void RapidFireBuff::buff_effect_when_applied() {
    pchar->get_stats()->increase_ranged_attack_speed(40);
}

void RapidFireBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_ranged_attack_speed(40);
}
