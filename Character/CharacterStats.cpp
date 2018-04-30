
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
    this->mh_haste = 0;
    this->oh_haste = 0;
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

float CharacterStats::get_mh_haste() {
    return mh_haste;
}

float CharacterStats::get_oh_haste() {
    return oh_haste;
}

void CharacterStats::increase_mh_haste(const float increase) {
    mh_haste += increase;
}

void CharacterStats::decrease_mh_haste(const float decrease) {
    mh_haste -= decrease;
}

void CharacterStats::increase_oh_haste(const float increase) {
    oh_haste += increase;
}

void CharacterStats::decrease_oh_haste(const float decrease) {
    oh_haste -= decrease;
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
}

void CharacterStats::decrease_hit(float decrease) {
    base_stats->decrease_hit(decrease);
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
    return pchar->has_mainhand() ? equipment->get_mainhand()->get_base_weapon_speed() / (1 + mh_haste) :
                                   2.0 / 1 + mh_haste;
}

float CharacterStats::get_oh_wpn_speed() {
    return pchar->has_offhand() ? equipment->get_offhand()->get_base_weapon_speed() / (1 + oh_haste) :
                                  300;
}
