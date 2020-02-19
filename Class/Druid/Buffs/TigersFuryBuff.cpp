#include "TigersFuryBuff.h"

#include "Character.h"
#include "CharacterStats.h"

TigersFuryBuff::TigersFuryBuff(Character* pchar) : SelfBuff(pchar, "Tiger's Fury", "Assets/ability/Ability_mount_jungletiger.png", 6, 0) {}

void TigersFuryBuff::buff_effect_when_applied() {
    pchar->get_stats()->increase_flat_physical_damage_bonus(flat_damage_bonus);
}

void TigersFuryBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_flat_physical_damage_bonus(flat_damage_bonus);
}
