#include "DefensiveStanceBuff.h"

#include "CharacterStats.h"
#include "Warrior.h"

DefensiveStanceBuff::DefensiveStanceBuff(Character* pchar):
    Buff(pchar, "Defensive Stance", NO_ICON, BuffDuration::PERMANENT, 1),
    warr(dynamic_cast<Warrior*>(pchar))
{
    this->hidden = true;
}

void DefensiveStanceBuff::buff_effect_when_applied() {
    warr->get_stats()->add_phys_damage_taken_mod(-10);
    warr->get_stats()->add_spell_damage_taken_mod(-10);
    warr->get_stats()->increase_total_phys_dmg_mod(-10);
}

void DefensiveStanceBuff::buff_effect_when_removed() {
    warr->get_stats()->remove_phys_damage_taken_mod(-10);
    warr->get_stats()->remove_spell_damage_taken_mod(-10);
    warr->get_stats()->decrease_total_phys_dmg_mod(-10);
}
