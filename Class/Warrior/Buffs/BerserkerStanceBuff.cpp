#include "BerserkerStanceBuff.h"

#include "CharacterStats.h"
#include "Warrior.h"

BerserkerStanceBuff::BerserkerStanceBuff(Character* pchar):
    SelfBuff(pchar, "Berserker Stance", NO_ICON, BuffDuration::PERMANENT, 1),
    warr(dynamic_cast<Warrior*>(pchar))
{
    this->hidden = true;
}

void BerserkerStanceBuff::buff_effect_when_applied() {
    warr->get_stats()->increase_melee_aura_crit(300);
    warr->get_stats()->add_phys_damage_taken_mod(10);
}

void BerserkerStanceBuff::buff_effect_when_removed() {
    warr->get_stats()->decrease_melee_aura_crit(300);
    warr->get_stats()->remove_phys_damage_taken_mod(10);
}
