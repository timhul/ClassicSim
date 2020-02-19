#include "ImprovedAspectOfTheHawkBuff.h"

#include "Character.h"

ImprovedAspectOfTheHawkBuff::ImprovedAspectOfTheHawkBuff(Character* pchar) :
    SelfBuff(pchar, "Improved Aspect of the Hawk", "Assets/ability/Ability_warrior_innerrage.png", 12.0, 0) {}

void ImprovedAspectOfTheHawkBuff::buff_effect_when_applied() {
    pchar->increase_ranged_attack_speed(30);
}

void ImprovedAspectOfTheHawkBuff::buff_effect_when_removed() {
    pchar->decrease_ranged_attack_speed(30);
}
