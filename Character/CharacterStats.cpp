
#include "CharacterStats.h"
#include "Character.h"
#include "Equipment.h"
#include "Stats.h"
#include "Race.h"
#include "CombatRoll.h"
#include "Target.h"
#include "Weapon.h"

CharacterStats::CharacterStats(Character* pchar, EquipmentDb *equipment_db, QObject* parent) :
    QObject(parent),
    pchar(pchar),
    equipment(new Equipment(equipment_db, pchar))
{
    this->base_stats = new Stats();
    this->total_phys_dmg_mod = 1.0;
    this->haste_factor = 1.0;
}

CharacterStats::~CharacterStats() {
    delete base_stats;
    delete equipment;
}

Equipment* CharacterStats::get_equipment() const {
    return this->equipment;
}

Stats* CharacterStats::get_stats() const {
    return this->base_stats;
}

int CharacterStats::get_strength() const {
    return base_stats->get_strength() + equipment->get_stats()->get_strength() + pchar->get_race()->get_base_strength();
}

int CharacterStats::get_agility() const {
    return base_stats->get_agility() + equipment->get_stats()->get_agility() + pchar->get_race()->get_base_agility();
}

int CharacterStats::get_stamina() const {
    return base_stats->get_stamina() + equipment->get_stats()->get_stamina() + pchar->get_race()->get_base_stamina();
}

int CharacterStats::get_intellect() const {
    return base_stats->get_intellect() + equipment->get_stats()->get_intellect() + pchar->get_race()->get_base_intellect();
}

int CharacterStats::get_spirit() const {
    return base_stats->get_spirit() + equipment->get_stats()->get_spirit() + pchar->get_race()->get_base_spirit();
}

double CharacterStats::get_hit_chance() const {
    return base_stats->get_hit_chance()  + equipment->get_stats()->get_hit_chance();
}

double CharacterStats::get_crit_chance() const {
    const double equip_effect = base_stats->get_crit_chance()  + equipment->get_stats()->get_crit_chance();
    const auto crit_from_agi = double(double(get_agility()) / pchar->get_agi_needed_for_one_percent_phys_crit());

    return equip_effect + crit_from_agi / 100;
}

void CharacterStats::increase_haste(const int increase) {
    attack_speed_buffs.append(increase);

    haste_factor = 1.0;
    for (int attack_speed_buff : attack_speed_buffs) {
        double haste_buff = double(attack_speed_buff) / 100;
        haste_factor *= 1 + haste_buff;
    }
}

void CharacterStats::decrease_haste(const int decrease) {
    assert(attack_speed_buffs.removeOne(decrease));

    haste_factor = 1.0;
    for (int attack_speed_buff : attack_speed_buffs) {
        double haste_buff = double(attack_speed_buff) / 100;
        haste_factor *= 1 + haste_buff;
    }
}

void CharacterStats::increase_strength(const int increase) {
    base_stats->increase_str(increase);
}

void CharacterStats::decrease_strength(const int decrease) {
    base_stats->decrease_str(decrease);
}

void CharacterStats::increase_agility(const int increase) {
    base_stats->increase_agi(increase);
}

void CharacterStats::decrease_agility(const int decrease) {
    base_stats->decrease_agi(decrease);
}

void CharacterStats::increase_stamina(const int increase) {
    base_stats->increase_stam(increase);
}

void CharacterStats::decrease_stamina(const int decrease) {
    base_stats->decrease_stam(decrease);
}

void CharacterStats::increase_intellect(const int increase) {
    base_stats->increase_int(increase);
}

void CharacterStats::decrease_intellect(const int decrease) {
    base_stats->decrease_int(decrease);
}

void CharacterStats::increase_spirit(const int increase) {
    base_stats->increase_spi(increase);
}

void CharacterStats::decrease_spirit(const int decrease) {
    base_stats->decrease_spi(decrease);
}

int CharacterStats::get_melee_ap() {
    int eq_base_melee_ap = equipment->get_stats()->get_melee_ap_str_excluded();
    int eq_str = equipment->get_stats()->get_strength();
    int eq_agi = equipment->get_stats()->get_agility();
    int eq_melee_ap = eq_base_melee_ap + eq_str * pchar->get_ap_per_strength() + eq_agi * pchar->get_ap_per_agi();
    int target_ap = equipment->get_stats()->get_melee_ap_against_type(pchar->get_combat_roll()->get_target()->get_creature_type());
    return base_stats->get_melee_ap_total()  + eq_melee_ap + target_ap;
}

void CharacterStats::increase_melee_ap(const int increase) {
    base_stats->increase_base_melee_ap(increase);
}

void CharacterStats::decrease_melee_ap(const int decrease) {
    base_stats->decrease_base_melee_ap(decrease);
}

double CharacterStats::get_total_phys_dmg_mod() const {
    return total_phys_dmg_mod;
}

void CharacterStats::increase_hit(double increase) {
    base_stats->increase_hit(increase);
    pchar->get_combat_roll()->update_miss_chance(get_hit_chance());
}

void CharacterStats::decrease_hit(double decrease) {
    base_stats->decrease_hit(decrease);
    pchar->get_combat_roll()->update_miss_chance(get_hit_chance());
}

void CharacterStats::increase_crit(double increase) {
    base_stats->increase_crit(increase);
    pchar->get_combat_roll()->update_crit_chance(get_crit_chance());
}

void CharacterStats::decrease_crit(double decrease) {
    base_stats->decrease_crit(decrease);
    pchar->get_combat_roll()->update_crit_chance(get_crit_chance());
}

void CharacterStats::increase_total_phys_dmg_mod(const int increase) {
    phys_dmg_buffs.append(increase);

    total_phys_dmg_mod = 1.0;
    for (int phys_dmg_buff : phys_dmg_buffs) {
        double coefficient = 1.0 + double(phys_dmg_buff) / 100;
        total_phys_dmg_mod = total_phys_dmg_mod * coefficient;
    }
}

void CharacterStats::decrease_total_phys_dmg_mod(const int decrease) {
    assert(phys_dmg_buffs.removeOne(decrease));

    total_phys_dmg_mod = 1.0;
    for (int phys_dmg_buff : phys_dmg_buffs) {
        double coefficient = 1.0 + double(phys_dmg_buff) / 100;
        total_phys_dmg_mod = total_phys_dmg_mod * coefficient;
    }
}

double CharacterStats::get_mh_wpn_speed() {
    return pchar->has_mainhand() ? equipment->get_mainhand()->get_base_weapon_speed() / haste_factor :
                                   2.0 / haste_factor;
}

double CharacterStats::get_oh_wpn_speed() {
    return pchar->has_offhand() ? equipment->get_offhand()->get_base_weapon_speed() / haste_factor :
                                  300;
}
