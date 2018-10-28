
#include "Stats.h"

Stats::Stats()
{
    this->STR = 0;
    this->AGI = 0;
    this->STAM = 0;
    this->INT = 0;
    this->SPI = 0;

    this->armor = 0;
    this->defense = 0;
    this->dodge_chance = 0.0;
    this->parry_chance = 0.0;

    this->arcane_res = 0;
    this->fire_res = 0;
    this->frost_res = 0;
    this->holy_res = 0;
    this->nature_res = 0;
    this->shadow_res = 0;

    this->axe_skill = 0;
    this->dagger_skill = 0;
    this->mace_skill = 0;
    this->sword_skill = 0;

    this->percent_hit = 0.0;
    this->percent_crit = 0.0;
    this->percent_spell_hit = 0.0;
    this->percent_spell_crit = 0.0;
    this->percent_attack_speed = 0.0;
    this->str_multiplier = 1.0;
    this->agi_multiplier = 1.0;
    this->stam_multiplier = 1.0;
    this->spi_multiplier = 1.0;
    this->int_multiplier = 1.0;

    this->melee_ap = 0;
    this->melee_ap_per_str = 1;
    this->melee_ap_per_agi = 1;

    this->ranged_ap = 0;
    this->ranged_ap_per_agi = 2;

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
}

Stats::~Stats() = default;

void Stats::add(const Stats* rhs) {
    increase_str(rhs->get_strength());
    increase_agi(rhs->get_agility());
    increase_stam(rhs->get_stamina());
    increase_int(rhs->get_intellect());
    increase_spi(rhs->get_spirit());

    // CSIM-72: Add getters to add/remove defensive stats.

    increase_axe_skill(rhs->get_axe_skill());
    increase_dagger_skill(rhs->get_dagger_skill());
    increase_mace_skill(rhs->get_mace_skill());
    increase_sword_skill(rhs->get_sword_skill());

    increase_hit(rhs->get_hit_chance());
    increase_crit(rhs->get_crit_chance());
    increase_attack_speed(rhs->get_attack_speed());

    increase_spell_hit(rhs->get_spell_hit_chance());
    increase_spell_crit(rhs->get_spell_crit_chance());

    increase_base_melee_ap(rhs->get_melee_ap_str_excluded());
    increase_base_ranged_ap(rhs->get_ranged_ap_agi_excluded());

    increase_melee_ap_against_type(Target::CreatureType::Beast, rhs->get_melee_ap_against_type(Target::CreatureType::Beast));
    increase_melee_ap_against_type(Target::CreatureType::Demon, rhs->get_melee_ap_against_type(Target::CreatureType::Demon));
    increase_melee_ap_against_type(Target::CreatureType::Dragonkin, rhs->get_melee_ap_against_type(Target::CreatureType::Dragonkin));
    increase_melee_ap_against_type(Target::CreatureType::Elemental, rhs->get_melee_ap_against_type(Target::CreatureType::Elemental));
    increase_melee_ap_against_type(Target::CreatureType::Giant, rhs->get_melee_ap_against_type(Target::CreatureType::Giant));
    increase_melee_ap_against_type(Target::CreatureType::Humanoid, rhs->get_melee_ap_against_type(Target::CreatureType::Humanoid));
    increase_melee_ap_against_type(Target::CreatureType::Mechanical, rhs->get_melee_ap_against_type(Target::CreatureType::Mechanical));
    increase_melee_ap_against_type(Target::CreatureType::Undead, rhs->get_melee_ap_against_type(Target::CreatureType::Undead));
}

void Stats::remove(const Stats* rhs) {
    decrease_str(rhs->get_strength());
    decrease_agi(rhs->get_agility());
    decrease_stam(rhs->get_stamina());
    decrease_int(rhs->get_intellect());
    decrease_spi(rhs->get_spirit());

    // CSIM-72: Add getters to add/remove defensive stats.

    decrease_axe_skill(rhs->get_axe_skill());
    decrease_dagger_skill(rhs->get_dagger_skill());
    decrease_mace_skill(rhs->get_mace_skill());
    decrease_sword_skill(rhs->get_sword_skill());

    decrease_hit(rhs->get_hit_chance());
    decrease_crit(rhs->get_crit_chance());
    decrease_attack_speed(rhs->get_attack_speed());

    decrease_spell_hit(rhs->get_spell_hit_chance());
    decrease_spell_crit(rhs->get_spell_crit_chance());

    decrease_base_melee_ap(rhs->get_melee_ap_str_excluded());
    decrease_base_ranged_ap(rhs->get_ranged_ap_agi_excluded());

    decrease_melee_ap_against_type(Target::CreatureType::Beast, rhs->get_melee_ap_against_type(Target::CreatureType::Beast));
    decrease_melee_ap_against_type(Target::CreatureType::Demon, rhs->get_melee_ap_against_type(Target::CreatureType::Demon));
    decrease_melee_ap_against_type(Target::CreatureType::Dragonkin, rhs->get_melee_ap_against_type(Target::CreatureType::Dragonkin));
    decrease_melee_ap_against_type(Target::CreatureType::Elemental, rhs->get_melee_ap_against_type(Target::CreatureType::Elemental));
    decrease_melee_ap_against_type(Target::CreatureType::Giant, rhs->get_melee_ap_against_type(Target::CreatureType::Giant));
    decrease_melee_ap_against_type(Target::CreatureType::Humanoid, rhs->get_melee_ap_against_type(Target::CreatureType::Humanoid));
    decrease_melee_ap_against_type(Target::CreatureType::Mechanical, rhs->get_melee_ap_against_type(Target::CreatureType::Mechanical));
    decrease_melee_ap_against_type(Target::CreatureType::Undead, rhs->get_melee_ap_against_type(Target::CreatureType::Undead));
}

int Stats::get_strength() const {
    return STR;
}

int Stats::get_agility() const {
    return AGI;
}

int Stats::get_stamina() const {
    return STAM;
}

int Stats::get_intellect() const {
    return int(double(INT) * int_multiplier);
}

int Stats::get_spirit() const {
    return int(double(SPI) * spi_multiplier);
}

void Stats::increase_str(const int increase) {
    STR += increase;
}

void Stats::decrease_str(const int decrease) {
    STR -= decrease;
}

void Stats::increase_agi(const int increase) {
    AGI += increase;
}

void Stats::decrease_agi(const int decrease) {
    AGI -= decrease;
}

void Stats::increase_stam(const int increase) {
    STAM += increase;
}

void Stats::decrease_stam(const int decrease) {
    STAM -= decrease;
}

void Stats::increase_int(const int increase) {
    INT += increase;
}

void Stats::decrease_int(const int decrease) {
    INT -= decrease;
}

void Stats::increase_spi(const int increase) {
    SPI += increase;
}

void Stats::decrease_spi(const int decrease) {
    SPI -= decrease;
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

void Stats::increase_all_resistances(const int increase) {
    increase_arcane_resistance(increase);
    increase_fire_resistance(increase);
    increase_frost_resistance(increase);
    increase_holy_resistance(increase);
    increase_nature_resistance(increase);
    increase_shadow_resistance(increase);
}

void Stats::decrease_all_resistances(const int decrease) {
    decrease_arcane_resistance(decrease);
    decrease_fire_resistance(decrease);
    decrease_frost_resistance(decrease);
    decrease_holy_resistance(decrease);
    decrease_nature_resistance(decrease);
    decrease_shadow_resistance(decrease);
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

int Stats::get_axe_skill() const {
    return axe_skill;
}

int Stats::get_dagger_skill() const {
    return dagger_skill;
}

int Stats::get_mace_skill() const {
    return mace_skill;
}

int Stats::get_sword_skill() const {
    return sword_skill;
}

void Stats::increase_axe_skill(const int increase) {
    axe_skill += increase;
}
void Stats::decrease_axe_skill(const int decrease) {
    axe_skill -= decrease;
}

void Stats::increase_dagger_skill(const int increase) {
    dagger_skill += increase;
}

void Stats::decrease_dagger_skill(const int decrease) {
    dagger_skill -= decrease;
}

void Stats::increase_mace_skill(const int increase) {
    mace_skill += increase;
}

void Stats::decrease_mace_skill(const int decrease) {
    mace_skill -= decrease;
}

void Stats::increase_sword_skill(const int increase) {
    sword_skill += increase;
}

void Stats::decrease_sword_skill(const int decrease) {
    sword_skill -= decrease;
}

int Stats::get_melee_ap_str_excluded() const {
    return melee_ap;
}

int Stats::get_melee_ap_total() const {
    return melee_ap + STR * melee_ap_per_str + AGI * melee_ap_per_agi;
}

void Stats::increase_base_melee_ap(const int increase) {
    melee_ap += increase;
}

void Stats::decrease_base_melee_ap(const int decrease) {
    melee_ap -= decrease;
}

int Stats::get_ranged_ap_agi_excluded() const {
    return ranged_ap;
}

int Stats::get_ranged_ap_total() const {
    return ranged_ap + AGI * ranged_ap_per_agi;
}

void Stats::increase_base_ranged_ap(const int increase) {
    ranged_ap += increase;
}

void Stats::decrease_base_ranged_ap(const int decrease) {
    ranged_ap -= decrease;
}

double Stats::get_hit_chance() const {
    return percent_hit;
}

double Stats::get_crit_chance() const {
    return percent_crit;
}

double Stats::get_spell_hit_chance() const {
    return percent_spell_hit;
}

double Stats::get_spell_crit_chance() const {
    return percent_spell_crit;
}

double Stats::get_attack_speed() const {
    return percent_attack_speed;
}

void Stats::set_melee_ap_per_str(const int value) {
    melee_ap_per_str = value;
}

void Stats::set_melee_ap_per_agi(const int value) {
    melee_ap_per_agi = value;
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

void Stats::increase_crit(const double value) {
    percent_crit += value;
}

void Stats::decrease_crit(const double value) {
    percent_crit -= value;
}

void Stats::increase_hit(const double value) {
    percent_hit += value;
}

void Stats::decrease_hit(const double value) {
    percent_hit -= value;
}

void Stats::increase_spell_hit(const double value) {
    percent_spell_hit += value;
}

void Stats::decrease_spell_hit(const double value) {
    percent_spell_hit -= value;
}

void Stats::increase_spell_crit(const double value) {
    percent_spell_crit += value;
}

void Stats::decrease_spell_crit(const double value) {
    percent_spell_crit -= value;
}

void Stats::increase_attack_speed(const double value) {
    percent_attack_speed += value;
}

void Stats::decrease_attack_speed(const double value) {
    percent_attack_speed -= value;
}

void Stats::increase_melee_ap_against_type(const Target::CreatureType type, const int increase) {
    melee_ap_against_creature[type] += increase;
}

void Stats::decrease_melee_ap_against_type(const Target::CreatureType type, const int decrease) {
    melee_ap_against_creature[type] -= decrease;
}

int Stats::get_melee_ap_against_type(const Target::CreatureType type) const {
    return melee_ap_against_creature[type];
}

void Stats::increase_ranged_ap_against_type(const Target::CreatureType type, const int increase) {
    ranged_ap_against_creature[type] += increase;
}

void Stats::decrease_ranged_ap_against_type(const Target::CreatureType type, const int decrease) {
    ranged_ap_against_creature[type] -= decrease;
}

int Stats::get_ranged_ap_against_type(const Target::CreatureType type) const {
    return ranged_ap_against_creature[type];
}
