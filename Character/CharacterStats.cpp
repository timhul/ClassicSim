
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
    this->attack_speed_mod = 1.0;
    this->physical_damage_taken_mod = 1.0;
    this->spell_damage_taken_mod = 1.0;
    this->total_stat_mod = 1.0;

    this->crit_bonuses_per_weapon_type.insert(WeaponTypes::AXE, 0.0);
    this->crit_bonuses_per_weapon_type.insert(WeaponTypes::TWOHAND_AXE, 0.0);
    this->crit_bonuses_per_weapon_type.insert(WeaponTypes::DAGGER, 0.0);
    this->crit_bonuses_per_weapon_type.insert(WeaponTypes::POLEARM, 0.0);
    this->crit_bonuses_per_weapon_type.insert(WeaponTypes::BOW, 0.0);
    this->crit_bonuses_per_weapon_type.insert(WeaponTypes::CROSSBOW, 0.0);
    this->crit_bonuses_per_weapon_type.insert(WeaponTypes::GUN, 0.0);

    this->damage_bonuses_per_weapon_type.insert(WeaponTypes::AXE, 0.0);
    this->damage_bonuses_per_weapon_type.insert(WeaponTypes::DAGGER, 0.0);
    this->damage_bonuses_per_weapon_type.insert(WeaponTypes::FIST, 0.0);
    this->damage_bonuses_per_weapon_type.insert(WeaponTypes::MACE, 0.0);
    this->damage_bonuses_per_weapon_type.insert(WeaponTypes::SWORD, 0.0);
    this->damage_bonuses_per_weapon_type.insert(WeaponTypes::TWOHAND_AXE, 0.0);
    this->damage_bonuses_per_weapon_type.insert(WeaponTypes::TWOHAND_MACE, 0.0);
    this->damage_bonuses_per_weapon_type.insert(WeaponTypes::TWOHAND_SWORD, 0.0);
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
    return static_cast<int>(round(total_stat_mod * (base_stats->get_strength() +
                                                    equipment->get_stats()->get_strength() +
                                                    pchar->get_race()->get_base_strength())));
}

int CharacterStats::get_agility() const {
    return static_cast<int>(round(total_stat_mod * (base_stats->get_agility() +
                                                    equipment->get_stats()->get_agility() +
                                                    pchar->get_race()->get_base_agility())));
}

int CharacterStats::get_stamina() const {
    return static_cast<int>(round(total_stat_mod * (base_stats->get_stamina() +
                                                    equipment->get_stats()->get_stamina() +
                                                    pchar->get_race()->get_base_stamina())));
}

int CharacterStats::get_intellect() const {
    return static_cast<int>(round(total_stat_mod * (base_stats->get_intellect() +
                                                    equipment->get_stats()->get_intellect() +
                                                    pchar->get_race()->get_base_intellect())));
}

int CharacterStats::get_spirit() const {
    return static_cast<int>(round(total_stat_mod * (base_stats->get_spirit() +
                                                    equipment->get_stats()->get_spirit() +
                                                    pchar->get_race()->get_base_spirit())));
}

double CharacterStats::get_hit_chance() const {
    return base_stats->get_hit_chance() + equipment->get_stats()->get_hit_chance();
}

double CharacterStats::get_mh_crit_chance() const {
    const double equip_effect = base_stats->get_crit_chance() + equipment->get_stats()->get_crit_chance();
    const auto crit_from_agi = double(get_agility()) / pchar->get_agi_needed_for_one_percent_phys_crit();

    double crit_from_wpn_type = 0.0;
    if (equipment->get_mainhand() != nullptr)
        crit_from_wpn_type = crit_bonuses_per_weapon_type[equipment->get_mainhand()->get_weapon_type()];

    return equip_effect + crit_from_agi / 100 + crit_from_wpn_type;
}

double CharacterStats::get_oh_crit_chance() const {
    double crit_from_wpn_type = 0.0;
    if (equipment->get_offhand() != nullptr)
        crit_from_wpn_type = crit_bonuses_per_weapon_type[equipment->get_offhand()->get_weapon_type()];
    else
        return 0.0;

    const double equip_effect = base_stats->get_crit_chance() + equipment->get_stats()->get_crit_chance();
    const auto crit_from_agi = double(get_agility()) / pchar->get_agi_needed_for_one_percent_phys_crit();

    return equip_effect + crit_from_agi / 100 + crit_from_wpn_type;;
}

double CharacterStats::get_spell_hit_chance() const {
    return base_stats->get_spell_hit_chance() + equipment->get_stats()->get_spell_hit_chance();
}

double CharacterStats::get_spell_crit_chance() const {
    const double equip_effect = base_stats->get_spell_crit_chance()  + equipment->get_stats()->get_spell_crit_chance();
    const auto crit_from_int = double(get_intellect()) / pchar->get_int_needed_for_one_percent_spell_crit();

    return equip_effect + crit_from_int / 100;
}

int CharacterStats::get_mh_wpn_skill() const {
    return get_wpn_skill(equipment->get_mainhand());
}

int CharacterStats::get_oh_wpn_skill() const {
    return get_wpn_skill(equipment->get_offhand());
}

int CharacterStats::get_wpn_skill(Weapon* weapon) const {
    if (weapon == nullptr)
        return pchar->get_clvl() * 5;

    int skill_bonus = 0;
    switch (weapon->get_weapon_type()) {
    case WeaponTypes::AXE:
    case WeaponTypes::TWOHAND_AXE:
        skill_bonus += pchar->get_race()->get_axe_bonus() + equipment->get_stats()->get_axe_skill();
        break;
    case WeaponTypes::DAGGER:
        skill_bonus += equipment->get_stats()->get_dagger_skill();
        break;
    case WeaponTypes::SWORD:
    case WeaponTypes::TWOHAND_SWORD:
        skill_bonus += pchar->get_race()->get_sword_bonus() + equipment->get_stats()->get_sword_skill();
        break;
    case WeaponTypes::MACE:
    case WeaponTypes::TWOHAND_MACE:
        skill_bonus += pchar->get_race()->get_mace_bonus() + equipment->get_stats()->get_mace_skill();
        break;
    }
    return pchar->get_clvl() * 5 + skill_bonus;
}

void CharacterStats::increase_haste(const int increase) {
    add_multiplicative_effect(attack_speed_buffs, increase, attack_speed_mod);
}

void CharacterStats::decrease_haste(const int decrease) {
    remove_multiplicative_effect(attack_speed_buffs, decrease, attack_speed_mod);
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

int CharacterStats::get_melee_ap() const {
    int eq_melee_ap = equipment->get_stats()->get_melee_ap_str_excluded();
    int attributes_ap = get_strength() * pchar->get_ap_per_strength() + get_agility() * pchar->get_ap_per_agi();
    int target_ap = equipment->get_stats()->get_melee_ap_against_type(pchar->get_target()->get_creature_type());
    return base_stats->get_melee_ap_total() + eq_melee_ap + attributes_ap + target_ap;
}

void CharacterStats::increase_melee_ap(const int increase) {
    base_stats->increase_base_melee_ap(increase);
}

void CharacterStats::decrease_melee_ap(const int decrease) {
    base_stats->decrease_base_melee_ap(decrease);
}

int CharacterStats::get_ranged_ap() const {
    int eq_ranged_ap = equipment->get_stats()->get_ranged_ap_agi_excluded();
    int attributes_ap = get_agility() * pchar->get_ap_per_agi();
    int target_ap = equipment->get_stats()->get_ranged_ap_against_type(pchar->get_target()->get_creature_type());
    return base_stats->get_ranged_ap_total() + eq_ranged_ap + attributes_ap + target_ap;
}

void CharacterStats::increase_ranged_ap(const int increase) {
    base_stats->increase_base_ranged_ap(increase);
}

void CharacterStats::decrease_ranged_ap(const int decrease) {
    base_stats->decrease_base_ranged_ap(decrease);
}

double CharacterStats::get_total_phys_dmg_mod() const {
    double dmg_bonus_from_wpn_type = 1.0;
    if (equipment->get_mainhand() != nullptr)
        dmg_bonus_from_wpn_type += double(damage_bonuses_per_weapon_type[equipment->get_mainhand()->get_weapon_type()]) / 100;

    return total_phys_dmg_mod * dmg_bonus_from_wpn_type;
}

double CharacterStats::get_attack_speed_mod() const {
    return attack_speed_mod;
}

double CharacterStats::get_physical_damage_taken_mod() const {
    return physical_damage_taken_mod;
}

double CharacterStats::get_spell_damage_taken_mod() const {
    return spell_damage_taken_mod;
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
}

void CharacterStats::decrease_crit(double decrease) {
    base_stats->decrease_crit(decrease);
}

void CharacterStats::increase_crit_for_weapon_type(const int weapon_type, const double increase) {
    crit_bonuses_per_weapon_type[weapon_type] += increase;
}

void CharacterStats::decrease_crit_for_weapon_type(const int weapon_type, const double decrease) {
    crit_bonuses_per_weapon_type[weapon_type] -= decrease;
}

void CharacterStats::increase_total_phys_dmg_for_weapon_type(const int weapon_type, const int increase) {
    damage_bonuses_per_weapon_type[weapon_type] += increase;
}

void CharacterStats::decrease_total_phys_dmg_for_weapon_type(const int weapon_type, const int decrease) {
    damage_bonuses_per_weapon_type[weapon_type] -= decrease;
}

void CharacterStats::increase_spell_hit(double increase) {
    base_stats->increase_spell_hit(increase);
    pchar->get_combat_roll()->update_spell_miss_chance(get_spell_hit_chance());
}

void CharacterStats::decrease_spell_hit(double decrease) {
    base_stats->decrease_spell_hit(decrease);
    pchar->get_combat_roll()->update_spell_miss_chance(get_spell_hit_chance());
}

void CharacterStats::increase_spell_crit(double increase) {
    base_stats->increase_spell_crit(increase);
    pchar->get_combat_roll()->update_spell_crit_chance(get_spell_crit_chance());
}

void CharacterStats::decrease_spell_crit(double decrease) {
    base_stats->decrease_spell_crit(decrease);
    pchar->get_combat_roll()->update_spell_miss_chance(get_spell_hit_chance());
}

void CharacterStats::increase_total_phys_dmg_mod(const int increase) {
    add_multiplicative_effect(phys_dmg_buffs, increase, total_phys_dmg_mod);
}

void CharacterStats::decrease_total_phys_dmg_mod(const int decrease) {
    remove_multiplicative_effect(phys_dmg_buffs, decrease, total_phys_dmg_mod);
}

void CharacterStats::add_phys_damage_taken_mod(const int mod) {
    add_multiplicative_effect(phys_damage_taken_changes, mod, physical_damage_taken_mod);
}

void CharacterStats::remove_phys_damage_taken_mod(const int mod) {
    remove_multiplicative_effect(phys_damage_taken_changes, mod, physical_damage_taken_mod);
}

void CharacterStats::add_spell_damage_taken_mod(const int mod) {
    add_multiplicative_effect(spell_damage_taken_changes, mod, spell_damage_taken_mod);
}

void CharacterStats::remove_spell_damage_taken_mod(const int mod) {
    remove_multiplicative_effect(spell_damage_taken_changes, mod, spell_damage_taken_mod);
}

void CharacterStats::add_total_stat_mod(const int mod) {
    add_multiplicative_effect(total_stat_mod_changes, mod, total_stat_mod);
}

void CharacterStats::remove_total_stat_mod(const int mod) {
    remove_multiplicative_effect(total_stat_mod_changes, mod, total_stat_mod);
}

double CharacterStats::get_mh_wpn_speed() {
    return pchar->has_mainhand() ? equipment->get_mainhand()->get_base_weapon_speed() / attack_speed_mod :
                                   2.0 / attack_speed_mod;
}

double CharacterStats::get_oh_wpn_speed() {
    return pchar->has_offhand() ? equipment->get_offhand()->get_base_weapon_speed() / attack_speed_mod :
                                  300;
}

void CharacterStats::add_multiplicative_effect(QVector<int>& effects, int add_value, double &modifier) {
    effects.append(add_value);

    recalculate_multiplicative_effects(effects, modifier);
}

void CharacterStats::remove_multiplicative_effect(QVector<int>& effects, int remove_value, double &modifier) {
    assert(effects.removeOne(remove_value));

    recalculate_multiplicative_effects(effects, modifier);
}

void CharacterStats::recalculate_multiplicative_effects(QVector<int>& effects, double& modifier) {
    modifier = 1.0;
    for (int effect : effects) {
        double coefficient = 1.0 + double(effect) / 100;
        modifier = modifier * coefficient;
    }

    assert(modifier > 0);
}


