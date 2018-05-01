
#include "CharacterStats.h"
#include "Character.h"
#include "Equipment.h"
#include "Stats.h"
#include "CombatRoll.h"

CharacterStats::CharacterStats(Character* pchar, Equipment* equipment, QObject* parent) :
    QObject(parent),
    pchar(pchar),
    equipment(equipment)
{
    this->base_stats = new Stats();
    this->total_phys_dmg_mod = 1.0;
    // TODO: Get haste enchants from gear
    this->haste_factor = 1.0;
}

CharacterStats::~CharacterStats() {
    delete base_stats;
}

Equipment* CharacterStats::get_equipment(void) const {
    return this->equipment;
}

Stats* CharacterStats::get_stats(void) const {
    return this->base_stats;
}

int CharacterStats::get_strength(void) {
    return base_stats->get_strength() + equipment->get_stats()->get_strength();
}

int CharacterStats::get_agility(void) {
    return base_stats->get_agility() + equipment->get_stats()->get_agility();
}

int CharacterStats::get_stamina(void) {
    return base_stats->get_stamina() + equipment->get_stats()->get_stamina();
}

int CharacterStats::get_intellect(void) {
    return base_stats->get_intellect() + equipment->get_stats()->get_intellect();
}

int CharacterStats::get_spirit(void) {
    return base_stats->get_spirit() + equipment->get_stats()->get_spirit();
}

float CharacterStats::get_hit_chance(void) const {
    return base_stats->get_hit_chance()  + equipment->get_stats()->get_hit_chance();
}

float CharacterStats::get_crit_chance(void) const {
    const float equip_effect = base_stats->get_crit_chance()  + equipment->get_stats()->get_crit_chance();
    const float crit_from_agi = float(float((base_stats->get_agility() + equipment->get_stats()->get_agility())) / pchar->get_agi_needed_for_one_percent_phys_crit());

    return equip_effect + crit_from_agi / 100;
}

void CharacterStats::increase_haste(const int increase) {
    attack_speed_buffs.append(increase);

    haste_factor = 1.0;
    for (int i = 0; i < attack_speed_buffs.size(); ++i) {
        float haste_buff = float(attack_speed_buffs[i]) / 100;
        haste_factor *= 1 + haste_buff;
    }
}

void CharacterStats::decrease_haste(const int decrease) {
    assert(attack_speed_buffs.removeOne(decrease));

    haste_factor = 1.0;
    for (int i = 0; i < attack_speed_buffs.size(); ++i) {
        float haste_buff = float(attack_speed_buffs[i]) / 100;
        haste_factor *= 1 + haste_buff;
    }
}

void CharacterStats::increase_strength(const int increase) {
    base_stats->increase_str(increase);
}

void CharacterStats::decrease_strength(const int decrease) {
    base_stats->decrease_str(decrease);
}

int CharacterStats::get_melee_ap() {
    return base_stats->get_melee_ap_total()  + equipment->get_stats()->get_melee_ap_total();
}

void CharacterStats::increase_melee_ap(const int increase) {
    base_stats->increase_base_melee_ap(increase);
}

void CharacterStats::decrease_melee_ap(const int decrease) {
    base_stats->decrease_base_melee_ap(decrease);
}

float CharacterStats::get_total_phys_dmg_mod() const {
    // TODO: Include e.g. Two-Handed Weapon Specialization if using 2-handers.
    return total_phys_dmg_mod;
}

void CharacterStats::increase_hit(float increase) {
    base_stats->increase_hit(increase);
    pchar->get_combat_roll()->update_miss_chance(get_hit_chance());
}

void CharacterStats::decrease_hit(float decrease) {
    base_stats->decrease_hit(decrease);
    pchar->get_combat_roll()->update_miss_chance(get_hit_chance());
}

void CharacterStats::increase_crit(float increase) {
    base_stats->increase_crit(increase);
    pchar->get_combat_roll()->update_crit_chance(get_crit_chance());
}

void CharacterStats::decrease_crit(float decrease) {
    base_stats->decrease_crit(decrease);
    pchar->get_combat_roll()->update_crit_chance(get_crit_chance());
}

void CharacterStats::increase_total_phys_dmg_mod(float increase) {
    total_phys_dmg_mod += increase;
}

void CharacterStats::decrease_total_phys_dmg_mod(float decrease) {
    total_phys_dmg_mod -= decrease;
}

float CharacterStats::get_mh_wpn_speed() {
    return pchar->has_mainhand() ? equipment->get_mainhand()->get_base_weapon_speed() / haste_factor :
                                   2.0 / haste_factor;
}

float CharacterStats::get_oh_wpn_speed() {
    return pchar->has_offhand() ? equipment->get_offhand()->get_base_weapon_speed() / haste_factor :
                                  300;
}

void CharacterStats::reset() {
    attack_speed_buffs.clear();
    haste_factor = 1.0;
    // TODO: Add +1% haste enchant from gear
}
