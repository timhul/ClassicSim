
#include "BloodFuryBuff.h"
#include "Character.h"
#include "CharacterStats.h"

void BloodFuryBuff::buff_effect_when_applied() {
    // [MeleeAp] = (base_strength * 2 + base_melee_ap) / 4
    // [102] = (123 * 2 + 160) / 4
    pchar->get_stats()->increase_melee_ap(102);
}

void BloodFuryBuff::buff_effect_when_removed() {
    // [MeleeAp] = (base_strength * 2 + base_melee_ap) / 4
    // [102] = (123 * 2 + 160) / 4
    pchar->get_stats()->decrease_melee_ap(102);
}
