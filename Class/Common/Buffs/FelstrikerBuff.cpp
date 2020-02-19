#include "FelstrikerBuff.h"

#include "Character.h"
#include "CharacterStats.h"

FelstrikerBuff::FelstrikerBuff(Character* pchar, const int duration) :
    SharedBuff(pchar, "Felstriker", "Assets/items/Inv_weapon_shortblade_25.png", duration, 0) {}

void FelstrikerBuff::buff_effect_when_applied() {
    pchar->get_stats()->increase_melee_aura_crit(10000);
    pchar->get_stats()->increase_melee_hit(10000);
}

void FelstrikerBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_melee_aura_crit(10000);
    pchar->get_stats()->decrease_melee_hit(10000);
}
