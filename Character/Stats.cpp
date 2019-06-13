#include "Stats.h"

#include "Utils/Check.h"

Stats::Stats() {
    this->melee_ap_against_creature[Target::CreatureType::Beast] = 0;
    this->melee_ap_against_creature[Target::CreatureType::Demon] = 0;
    this->melee_ap_against_creature[Target::CreatureType::Dragonkin] = 0;
    this->melee_ap_against_creature[Target::CreatureType::Elemental] = 0;
    this->melee_ap_against_creature[Target::CreatureType::Giant] = 0;
    this->melee_ap_against_creature[Target::CreatureType::Humanoid] = 0;
    this->melee_ap_against_creature[Target::CreatureType::Mechanical] = 0;
    this->melee_ap_against_creature[Target::CreatureType::Undead] = 0;

    this->ranged_ap_against_creature[Target::CreatureType::Beast] = 0;
    this->ranged_ap_against_creature[Target::CreatureType::Demon] = 0;
    this->ranged_ap_against_creature[Target::CreatureType::Dragonkin] = 0;
    this->ranged_ap_against_creature[Target::CreatureType::Elemental] = 0;
    this->ranged_ap_against_creature[Target::CreatureType::Giant] = 0;
    this->ranged_ap_against_creature[Target::CreatureType::Humanoid] = 0;
    this->ranged_ap_against_creature[Target::CreatureType::Mechanical] = 0;
    this->ranged_ap_against_creature[Target::CreatureType::Undead] = 0;

    this->spell_school_damage_bonus[MagicSchool::Arcane] = 0;
    this->spell_school_damage_bonus[MagicSchool::Fire] = 0;
    this->spell_school_damage_bonus[MagicSchool::Frost] = 0;
    this->spell_school_damage_bonus[MagicSchool::Holy] = 0;
    this->spell_school_damage_bonus[MagicSchool::Nature] = 0;
    this->spell_school_damage_bonus[MagicSchool::Physical] = 0;
    this->spell_school_damage_bonus[MagicSchool::Shadow] = 0;
}

void Stats::add(const Stats* rhs) {
    increase_strength(rhs->get_strength());
    increase_agility(rhs->get_agility());
    increase_stamina(rhs->get_stamina());
    increase_intellect(rhs->get_intellect());
    increase_spirit(rhs->get_spirit());

    // CSIM-72: Add getters to add/remove defensive stats.

    increase_axe_skill(rhs->get_axe_skill());
    increase_dagger_skill(rhs->get_dagger_skill());
    increase_mace_skill(rhs->get_mace_skill());
    increase_sword_skill(rhs->get_sword_skill());
    increase_bow_skill(rhs->get_bow_skill());
    increase_crossbow_skill(rhs->get_crossbow_skill());
    increase_gun_skill(rhs->get_gun_skill());

    increase_melee_hit(rhs->get_melee_hit_chance());
    increase_melee_crit(rhs->get_melee_crit_chance());
    increase_ranged_hit(rhs->get_ranged_hit_chance());
    increase_ranged_crit(rhs->get_ranged_crit_chance());
    increase_attack_speed(rhs->get_attack_speed());

    increase_spell_hit(rhs->get_spell_hit_chance());
    increase_spell_crit(rhs->get_spell_crit_chance());

    increase_base_melee_ap(rhs->get_base_melee_ap());
    increase_base_ranged_ap(rhs->get_base_ranged_ap());

    increase_melee_ap_against_type(Target::CreatureType::Beast, rhs->get_melee_ap_against_type(Target::CreatureType::Beast));
    increase_melee_ap_against_type(Target::CreatureType::Demon, rhs->get_melee_ap_against_type(Target::CreatureType::Demon));
    increase_melee_ap_against_type(Target::CreatureType::Dragonkin, rhs->get_melee_ap_against_type(Target::CreatureType::Dragonkin));
    increase_melee_ap_against_type(Target::CreatureType::Elemental, rhs->get_melee_ap_against_type(Target::CreatureType::Elemental));
    increase_melee_ap_against_type(Target::CreatureType::Giant, rhs->get_melee_ap_against_type(Target::CreatureType::Giant));
    increase_melee_ap_against_type(Target::CreatureType::Humanoid, rhs->get_melee_ap_against_type(Target::CreatureType::Humanoid));
    increase_melee_ap_against_type(Target::CreatureType::Mechanical, rhs->get_melee_ap_against_type(Target::CreatureType::Mechanical));
    increase_melee_ap_against_type(Target::CreatureType::Undead, rhs->get_melee_ap_against_type(Target::CreatureType::Undead));

    increase_flat_weapon_damage(rhs->get_flat_weapon_damage());

    increase_mp5(rhs->get_mp5());
    increase_base_spell_damage(rhs->get_base_spell_damage());
}

void Stats::remove(const Stats* rhs) {
    decrease_strength(rhs->get_strength());
    decrease_agility(rhs->get_agility());
    decrease_stamina(rhs->get_stamina());
    decrease_intellect(rhs->get_intellect());
    decrease_spirit(rhs->get_spirit());

    // CSIM-72: Add getters to add/remove defensive stats.

    decrease_axe_skill(rhs->get_axe_skill());
    decrease_dagger_skill(rhs->get_dagger_skill());
    decrease_mace_skill(rhs->get_mace_skill());
    decrease_sword_skill(rhs->get_sword_skill());
    decrease_bow_skill(rhs->get_bow_skill());
    decrease_crossbow_skill(rhs->get_crossbow_skill());
    decrease_gun_skill(rhs->get_gun_skill());

    decrease_melee_hit(rhs->get_melee_hit_chance());
    decrease_melee_crit(rhs->get_melee_crit_chance());
    decrease_ranged_hit(rhs->get_ranged_hit_chance());
    decrease_ranged_crit(rhs->get_ranged_crit_chance());
    decrease_attack_speed(rhs->get_attack_speed());

    decrease_spell_hit(rhs->get_spell_hit_chance());
    decrease_spell_crit(rhs->get_spell_crit_chance());

    decrease_base_melee_ap(rhs->get_base_melee_ap());
    decrease_base_ranged_ap(rhs->get_base_ranged_ap());

    decrease_melee_ap_against_type(Target::CreatureType::Beast, rhs->get_melee_ap_against_type(Target::CreatureType::Beast));
    decrease_melee_ap_against_type(Target::CreatureType::Demon, rhs->get_melee_ap_against_type(Target::CreatureType::Demon));
    decrease_melee_ap_against_type(Target::CreatureType::Dragonkin, rhs->get_melee_ap_against_type(Target::CreatureType::Dragonkin));
    decrease_melee_ap_against_type(Target::CreatureType::Elemental, rhs->get_melee_ap_against_type(Target::CreatureType::Elemental));
    decrease_melee_ap_against_type(Target::CreatureType::Giant, rhs->get_melee_ap_against_type(Target::CreatureType::Giant));
    decrease_melee_ap_against_type(Target::CreatureType::Humanoid, rhs->get_melee_ap_against_type(Target::CreatureType::Humanoid));
    decrease_melee_ap_against_type(Target::CreatureType::Mechanical, rhs->get_melee_ap_against_type(Target::CreatureType::Mechanical));
    decrease_melee_ap_against_type(Target::CreatureType::Undead, rhs->get_melee_ap_against_type(Target::CreatureType::Undead));

    decrease_flat_weapon_damage(rhs->get_flat_weapon_damage());

    decrease_mp5(rhs->get_mp5());
    decrease_base_spell_damage(rhs->get_base_spell_damage());
}

int Stats::get_armor() const {
    return armor;
}

unsigned Stats::get_strength() const {
    return strength;
}

unsigned Stats::get_agility() const {
    return agility;
}

unsigned Stats::get_stamina() const {
    return stamina;
}

unsigned Stats::get_intellect() const {
    return static_cast<unsigned>(round(intellect * int_multiplier));
}

unsigned Stats::get_spirit() const {
    return static_cast<unsigned>(round(spirit * spi_multiplier));
}

void Stats::increase_strength(const unsigned increase) {
    strength += increase;
}

void Stats::decrease_strength(const unsigned decrease) {
    strength -= decrease;
}

void Stats::increase_agility(const unsigned increase) {
    agility += increase;
}

void Stats::decrease_agility(const unsigned decrease) {
    agility -= decrease;
}

void Stats::increase_stamina(const unsigned increase) {
    stamina += increase;
}

void Stats::decrease_stamina(const unsigned decrease) {
    stamina -= decrease;
}

void Stats::increase_intellect(const unsigned increase) {
    intellect += increase;
}

void Stats::decrease_intellect(const unsigned decrease) {
    intellect -= decrease;
}

void Stats::increase_spirit(const unsigned increase) {
    spirit += increase;
}

void Stats::decrease_spirit(const unsigned decrease) {
    spirit -= decrease;
}

void Stats::increase_armor(const int increase) {
    armor += increase;
}

void Stats::decrease_armor(const int decrease) {
    armor -= decrease;
}

void Stats::increase_defense(const int increase) {
    defense += increase;
}

void Stats::decrease_defense(const int decrease) {
    defense -= decrease;
}

void Stats::increase_dodge(const double increase) {
    dodge_chance += increase;
}

void Stats::decrease_dodge(const double decrease) {
    dodge_chance -= decrease;
}

void Stats::increase_parry(const double increase) {
    parry_chance += increase;
}

void Stats::decrease_parry(const double decrease) {
    parry_chance -= decrease;
}

void Stats::increase_arcane_resistance(const int increase) {
    arcane_res += increase;
}

void Stats::decrease_arcane_resistance(const int decrease) {
    arcane_res -= decrease;
}

void Stats::increase_fire_resistance(const int increase) {
    fire_res += increase;
}

void Stats::decrease_fire_resistance(const int decrease) {
    fire_res -= decrease;
}

void Stats::increase_frost_resistance(const int increase) {
    frost_res += increase;
}

void Stats::decrease_frost_resistance(const int decrease) {
    frost_res -= decrease;
}

void Stats::increase_holy_resistance(const int increase) {
    holy_res += increase;
}

void Stats::decrease_holy_resistance(const int decrease) {
    holy_res -= decrease;
}

void Stats::increase_nature_resistance(const int increase) {
    nature_res += increase;
}

void Stats::decrease_nature_resistance(const int decrease) {
    nature_res -= decrease;
}

void Stats::increase_shadow_resistance(const int increase) {
    shadow_res += increase;
}

void Stats::decrease_shadow_resistance(const int decrease) {
    shadow_res -= decrease;
}

unsigned Stats::get_axe_skill() const {
    return axe_skill;
}

void Stats::increase_axe_skill(const unsigned value) {
    axe_skill += value;
}
void Stats::decrease_axe_skill(const unsigned value) {
    axe_skill -= value;
}

unsigned Stats::get_dagger_skill() const {
    return dagger_skill;
}

void Stats::increase_dagger_skill(const unsigned value) {
    dagger_skill += value;
}

void Stats::decrease_dagger_skill(const unsigned value) {
    dagger_skill -= value;
}

unsigned Stats::get_mace_skill() const {
    return mace_skill;
}

void Stats::increase_mace_skill(const unsigned value) {
    mace_skill += value;
}

void Stats::decrease_mace_skill(const unsigned value) {
    mace_skill -= value;
}

unsigned Stats::get_sword_skill() const {
    return sword_skill;
}

void Stats::increase_sword_skill(const unsigned value) {
    sword_skill += value;
}

void Stats::decrease_sword_skill(const unsigned value) {
    sword_skill -= value;
}

unsigned Stats::get_bow_skill() const {
    return bow_skill;
}

void Stats::increase_bow_skill(const unsigned value) {
    bow_skill += value;
}

void Stats::decrease_bow_skill(const unsigned value) {
    bow_skill -= value;
}

unsigned Stats::get_crossbow_skill() const {
    return crossbow_skill;
}

void Stats::increase_crossbow_skill(const unsigned value) {
    crossbow_skill += value;
}

void Stats::decrease_crossbow_skill(const unsigned value) {
    crossbow_skill -= value;
}

unsigned Stats::get_gun_skill() const {
    return gun_skill;
}

void Stats::increase_gun_skill(const unsigned value) {
    gun_skill += value;
}

void Stats::decrease_gun_skill(const unsigned value) {
    gun_skill -= value;
}

unsigned Stats::get_base_melee_ap() const {
    return melee_ap;
}

void Stats::increase_base_melee_ap(const unsigned increase) {
    melee_ap += increase;
}

void Stats::decrease_base_melee_ap(const unsigned decrease) {
    check((melee_ap >= decrease), "Underflow decrease");
    melee_ap -= decrease;
}

unsigned Stats::get_base_ranged_ap() const {
    return ranged_ap;
}

void Stats::increase_base_ranged_ap(const unsigned increase) {
    ranged_ap += increase;
}

void Stats::decrease_base_ranged_ap(const unsigned decrease) {
    check((ranged_ap >= decrease), "Underflow decrease");
    ranged_ap -= decrease;
}

unsigned Stats::get_melee_hit_chance() const {
    return melee_hit;
}

unsigned Stats::get_ranged_hit_chance() const {
    return ranged_hit;
}

unsigned Stats::get_melee_crit_chance() const {
    return melee_crit;
}

unsigned Stats::get_ranged_crit_chance() const {
    return ranged_crit;
}

unsigned Stats::get_spell_hit_chance() const {
    return spell_hit;
}

unsigned Stats::get_spell_crit_chance() const {
    return spell_crit;
}

unsigned Stats::get_attack_speed() const {
    return attack_speed;
}

void Stats::set_str_multiplier(const double value) {
    str_multiplier = value;
}

void Stats::set_agi_multiplier(const double value) {
    agi_multiplier = value;
}

void Stats::set_stam_multiplier(const double value) {
    stam_multiplier = value;
}

void Stats::set_spi_multiplier(const double value) {
    spi_multiplier = value;
}

void Stats::set_int_multiplier(const double value) {
    int_multiplier = value;
}

void Stats::increase_melee_crit(const unsigned value) {
    melee_crit += value;
}

void Stats::decrease_melee_crit(const unsigned value) {
    melee_crit -= value;
}

void Stats::increase_melee_hit(const unsigned value) {
    melee_hit += value;
}

void Stats::decrease_melee_hit(const unsigned value) {
    melee_hit -= value;
}

void Stats::increase_ranged_hit(const unsigned value) {
    ranged_hit += value;
}

void Stats::decrease_ranged_hit(const unsigned value) {
    ranged_hit -= value;
}

void Stats::increase_ranged_crit(const unsigned value) {
    ranged_crit += value;
}

void Stats::decrease_ranged_crit(const unsigned value) {
    ranged_crit -= value;
}

void Stats::increase_spell_hit(const unsigned value) {
    spell_hit += value;
}

void Stats::decrease_spell_hit(const unsigned value) {
    spell_hit -= value;
}

void Stats::increase_spell_crit(const unsigned value) {
    spell_crit += value;
}

void Stats::decrease_spell_crit(const unsigned value) {
    spell_crit -= value;
}

void Stats::increase_attack_speed(const unsigned value) {
    attack_speed += value;
}

void Stats::decrease_attack_speed(const unsigned value) {
    attack_speed -= value;
}

void Stats::increase_melee_ap_against_type(const Target::CreatureType type, const unsigned increase) {
    melee_ap_against_creature[type] += increase;
}

void Stats::decrease_melee_ap_against_type(const Target::CreatureType type, const unsigned decrease) {
    melee_ap_against_creature[type] -= decrease;
}

unsigned Stats::get_melee_ap_against_type(const Target::CreatureType type) const {
    return melee_ap_against_creature[type];
}

void Stats::increase_ranged_ap_against_type(const Target::CreatureType type, const unsigned increase) {
    ranged_ap_against_creature[type] += increase;
}

void Stats::decrease_ranged_ap_against_type(const Target::CreatureType type, const unsigned decrease) {
    ranged_ap_against_creature[type] -= decrease;
}

unsigned Stats::get_ranged_ap_against_type(const Target::CreatureType type) const {
    return ranged_ap_against_creature[type];
}

unsigned Stats::get_flat_weapon_damage() const {
    return flat_weapon_damage;
}

void Stats::increase_flat_weapon_damage(const unsigned value) {
    flat_weapon_damage += value;
}

void Stats::decrease_flat_weapon_damage(const unsigned value) {
    check((value <= flat_weapon_damage), "Underflow decrease flat_weapon_damage");
    flat_weapon_damage -= value;
}

unsigned Stats::get_mp5() const {
    return mp5;
}

void Stats::increase_mp5(const unsigned increase) {
    mp5 += increase;
}

void Stats::decrease_mp5(const unsigned decrease) {
    check((decrease <= mp5), "Underflow decrease mp5");
    mp5 -= decrease;
}

unsigned Stats::get_base_spell_damage() const {
    return spell_damage;
}

void Stats::increase_base_spell_damage(const unsigned increase) {
    spell_damage += increase;
}

void Stats::decrease_base_spell_damage(const unsigned decrease) {
    check((decrease <= spell_damage), "Underflow decrease spell_damage");
    spell_damage -= decrease;
}

unsigned Stats::get_spell_damage(const MagicSchool school) const {
    return get_base_spell_damage() + spell_school_damage_bonus[school];
}

void Stats::increase_spell_damage_vs_school(const unsigned increase, const MagicSchool school) {
    spell_school_damage_bonus[school] += increase;
}

void Stats::decrease_spell_damage_vs_school(const unsigned decrease, const MagicSchool school) {
    check((decrease <= spell_school_damage_bonus[school]), "Underflow decrease");
    spell_school_damage_bonus[school] -= decrease;
}
