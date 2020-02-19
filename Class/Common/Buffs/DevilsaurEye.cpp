#include "DevilsaurEye.h"

#include "Character.h"
#include "CharacterStats.h"

DevilsaurEye::DevilsaurEye(Character* pchar) : SelfBuff(pchar, "Devilsaur Eye", "Assets/items/Inv_misc_eye_01.png", 20, 0) {}

void DevilsaurEye::buff_effect_when_applied() {
    pchar->get_stats()->increase_melee_ap(150);
    pchar->get_stats()->increase_ranged_ap(150);

    pchar->get_stats()->increase_melee_hit(200);
    pchar->get_stats()->increase_ranged_hit(200);
}

void DevilsaurEye::buff_effect_when_removed() {
    pchar->get_stats()->decrease_melee_ap(150);
    pchar->get_stats()->decrease_ranged_ap(150);

    pchar->get_stats()->decrease_melee_hit(200);
    pchar->get_stats()->decrease_ranged_hit(200);
}
