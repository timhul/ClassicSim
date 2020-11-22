#include "DefensiveStanceBuff.h"

#include <cmath>
#include <vector>

#include "CharacterStats.h"
#include "Warrior.h"

DefensiveStanceBuff::DefensiveStanceBuff(Warrior* warrior) :
    SelfBuff(warrior, "Defensive Stance", NO_ICON, BuffDuration::PERMANENT, 1),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo("Defiance", 5, DisabledAtZero::No)}),
    warrior(warrior),
    current_threat_mod(30) {
    this->hidden = true;
}

void DefensiveStanceBuff::increase_talent_rank_effect(const QString& /* talent_name */, const int curr) {
    if (warrior->in_defensive_stance())
        warrior->get_stats()->decrease_total_threat_mod(std::round(current_threat_mod));
    current_threat_mod = (130 * (1 + 0.03 * curr)) - 100;
    if (warrior->in_defensive_stance())
        warrior->get_stats()->increase_total_threat_mod(std::round(current_threat_mod));
}

void DefensiveStanceBuff::decrease_talent_rank_effect(const QString& /* talent_name */, const int curr) {
    if (warrior->in_defensive_stance())
        warrior->get_stats()->decrease_total_threat_mod(std::round(current_threat_mod));
    current_threat_mod = (130 * (1 + 0.03 * curr)) - 100;
    if (warrior->in_defensive_stance())
        warrior->get_stats()->increase_total_threat_mod(std::round(current_threat_mod));
}

void DefensiveStanceBuff::buff_effect_when_applied() {
    warrior->get_stats()->add_phys_damage_taken_mod(-10);
    warrior->get_stats()->add_spell_damage_taken_mod(-10);
    warrior->get_stats()->increase_total_phys_dmg_mod(-10);
    warrior->get_stats()->increase_total_threat_mod(std::round(current_threat_mod));
}

void DefensiveStanceBuff::buff_effect_when_removed() {
    warrior->get_stats()->remove_phys_damage_taken_mod(-10);
    warrior->get_stats()->remove_spell_damage_taken_mod(-10);
    warrior->get_stats()->decrease_total_phys_dmg_mod(-10);
    warrior->get_stats()->decrease_total_threat_mod(std::round(current_threat_mod));
}
