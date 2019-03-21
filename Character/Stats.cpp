#include "Stats.h"

#include "Utils/Check.h"

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

    increase_hit(rhs->get_hit_chance());
    increase_crit(rhs->get_crit_chance());
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

    decrease_hit(rhs->get_hit_chance());
    decrease_crit(rhs->get_crit_chance());
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
}

unsigned Stats::get_strength() const {
    return STR;
}

unsigned Stats::get_agility() const {
    return AGI;
}

unsigned Stats::get_stamina() const {
    return STAM;
}

unsigned Stats::get_intellect() const {
    return static_cast<unsigned>(round(INT * int_multiplier));
}

unsigned Stats::get_spirit() const {
    return static_cast<unsigned>(round(SPI * spi_multiplier));
}

void Stats::increase_strength(const unsigned increase) {
    STR += increase;
}

void Stats::decrease_strength(const unsigned decrease) {
    STR -= decrease;
}

void Stats::increase_agility(const unsigned increase) {
    AGI += increase;
}

void Stats::decrease_agility(const unsigned decrease) {
    AGI -= decrease;
}

void Stats::increase_stamina(const unsigned increase) {
    STAM += increase;
}

void Stats::decrease_stamina(const unsigned decrease) {
    STAM -= decrease;
}

void Stats::increase_intellect(const unsigned increase) {
    INT += increase;
}

void Stats::decrease_intellect(const unsigned decrease) {
    INT -= decrease;
}

void Stats::increase_spirit(const unsigned increase) {
    SPI += increase;
}

void Stats::decrease_spirit(const unsigned decrease) {
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

void Stats::set_melee_ap_per_str(const unsigned value) {
    melee_ap_per_str = value;
}

void Stats::set_melee_ap_per_agi(const unsigned value) {
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
