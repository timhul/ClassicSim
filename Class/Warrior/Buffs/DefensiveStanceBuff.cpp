#include "DefensiveStanceBuff.h"

#include "CharacterStats.h"
#include "Warrior.h"

DefensiveStanceBuff::DefensiveStanceBuff(Warrior* warrior) :
    SelfBuff(warrior, "Defensive Stance", NO_ICON, BuffDuration::PERMANENT, 1), warrior(warrior) {
    this->hidden = true;
}

void DefensiveStanceBuff::buff_effect_when_applied() {
    warrior->get_stats()->add_phys_damage_taken_mod(-10);
    warrior->get_stats()->add_spell_damage_taken_mod(-10);
    warrior->get_stats()->increase_total_phys_dmg_mod(-10);
    warrior->get_stats()->increase_total_threat_mod(50);
}

void DefensiveStanceBuff::buff_effect_when_removed() {
    warrior->get_stats()->remove_phys_damage_taken_mod(-10);
    warrior->get_stats()->remove_spell_damage_taken_mod(-10);
    warrior->get_stats()->decrease_total_phys_dmg_mod(-10);
    warrior->get_stats()->decrease_total_threat_mod(50);
}
