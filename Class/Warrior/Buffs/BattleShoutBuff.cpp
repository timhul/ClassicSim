#include "BattleShoutBuff.h"

#include "CharacterStats.h"
#include "Warrior.h"

BattleShoutBuff::BattleShoutBuff(Warrior* pchar):
    PartyBuff(pchar, "Battle Shout", "Assets/ability/Ability_warrior_battleshout.png",  120, 0)
{}

void BattleShoutBuff::buff_effect_when_applied() {
    pchar->get_stats()->increase_melee_ap(attack_power);
}

void BattleShoutBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_melee_ap(attack_power);
}
