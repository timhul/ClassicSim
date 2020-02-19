#include "BerserkerStanceBuff.h"

#include "CharacterStats.h"
#include "Warrior.h"

BerserkerStanceBuff::BerserkerStanceBuff(Warrior* warrior) :
    SelfBuff(warrior, "Berserker Stance", NO_ICON, BuffDuration::PERMANENT, 1), warrior(warrior) {
    this->hidden = true;
}

void BerserkerStanceBuff::buff_effect_when_applied() {
    warrior->get_stats()->increase_melee_aura_crit(300);
    warrior->get_stats()->add_phys_damage_taken_mod(10);
    warrior->get_stats()->increase_total_threat_mod(-10);
}

void BerserkerStanceBuff::buff_effect_when_removed() {
    warrior->get_stats()->decrease_melee_aura_crit(300);
    warrior->get_stats()->remove_phys_damage_taken_mod(10);
    warrior->get_stats()->decrease_total_threat_mod(-10);
}
