#include "BloodFuryBuff.h"

#include "Character.h"
#include "CharacterStats.h"
#include <cmath>

BloodFuryBuff::BloodFuryBuff(Character *pchar) :
    SelfBuff(pchar, "Blood Fury", "Assets/races/Racial_orc_berserkerstrength.png", 15, 1)
{}

void BloodFuryBuff::buff_effect_when_applied() {
    applied_ap = static_cast<unsigned>(round((160 + pchar->get_stats()->get_strength() * pchar->get_melee_ap_per_strength()) * 0.25 + pchar->get_stats()->get_agility() * pchar->get_melee_ap_per_agi()));
    pchar->get_stats()->increase_melee_ap(applied_ap);
}

void BloodFuryBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_melee_ap(applied_ap);
}
