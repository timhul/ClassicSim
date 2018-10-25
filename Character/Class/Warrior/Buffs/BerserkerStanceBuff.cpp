
#include "BerserkerStanceBuff.h"
#include "Warrior.h"
#include "CharacterStats.h"

BerserkerStanceBuff::BerserkerStanceBuff(Character* pchar):
    Buff(pchar, "Berserker Stance", NO_ICON, BuffDuration::PERMANENT, 1),
    warr(dynamic_cast<Warrior*>(pchar))
{
    this->hidden = true;
}

void BerserkerStanceBuff::buff_effect_when_applied() {
    warr->get_stats()->increase_crit(0.03);
    warr->get_stats()->add_phys_damage_taken_mod(10);
}

void BerserkerStanceBuff::buff_effect_when_removed() {
    warr->get_stats()->decrease_crit(0.03);
    warr->get_stats()->remove_phys_damage_taken_mod(10);
}
