
#include "Stats.h"
#include "Character.h"
#include "Race.h"
#include <QDebug>

Stats::Stats(QObject* parent ) :
    QObject(parent)
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
    this->percent_attack_speed = 0.0;
    this->str_multiplier = 1.0;
    this->agi_multiplier = 1.0;
    this->stam_multiplier = 1.0;
    this->spi_multiplier = 1.0;
    this->int_multiplier = 1.0;

    this->melee_ap = 0;
    this->melee_ap_per_str = 1;
    this->melee_ap_per_agi = 1;
}

Stats::~Stats()
{}

void Stats::add(const Stats* rhs) {
    increase_str(rhs->get_strength());
    increase_agi(rhs->get_agility());
    increase_stam(rhs->get_stamina());
    increase_int(rhs->get_intellect());
    increase_spi(rhs->get_spirit());

    // TODO: Add getters to add/remove defensive stats.

    increase_axe_skill(rhs->get_axe_skill());
    increase_dagger_skill(rhs->get_dagger_skill());
    increase_mace_skill(rhs->get_mace_skill());
    increase_sword_skill(rhs->get_sword_skill());

    increase_hit(rhs->get_hit_chance());
    increase_crit(rhs->get_crit_chance());
    // TODO: Attack speed missing.

    increase_base_melee_ap(rhs->get_melee_ap_str_excluded());
}

void Stats::remove(const Stats* rhs) {
    decrease_str(rhs->get_strength());
    decrease_agi(rhs->get_agility());
    decrease_stam(rhs->get_stamina());
    decrease_int(rhs->get_intellect());
    decrease_spi(rhs->get_spirit());

    // TODO: Add getters to add/remove defensive stats.

    decrease_axe_skill(rhs->get_axe_skill());
    decrease_dagger_skill(rhs->get_dagger_skill());
    decrease_mace_skill(rhs->get_mace_skill());
    decrease_sword_skill(rhs->get_sword_skill());

    decrease_hit(rhs->get_hit_chance());
    decrease_crit(rhs->get_crit_chance());
    // TODO: Attack speed missing.

    decrease_base_melee_ap(rhs->get_melee_ap_str_excluded());
}

int Stats::get_strength(void) const {
    return STR;
}

int Stats::get_agility(void) const {
    return AGI;
}

int Stats::get_stamina(void) const {
    return STAM;
}

int Stats::get_intellect(void) const {
    return int(float(INT) * int_multiplier);
}

int Stats::get_spirit(void) const {
    return int(float(SPI) * spi_multiplier);
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

void Stats::increase_dodge(const float increase) {
    dodge_chance += increase;
}

void Stats::decrease_dodge(const float decrease) {
    dodge_chance -= decrease;
}

void Stats::increase_parry(const float increase) {
    parry_chance += increase;
}

void Stats::decrease_parry(const float decrease) {
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

float Stats::get_hit_chance(void) const {
    return percent_hit;
}

float Stats::get_crit_chance(void) const {
    return percent_crit;
}

void Stats::set_melee_ap_per_str(const int value) {
    melee_ap_per_str = value;
}

void Stats::set_melee_ap_per_agi(const int value) {
    melee_ap_per_agi = value;
}

void Stats::set_str_multiplier(const float value) {
    str_multiplier = value;
}

void Stats::set_agi_multiplier(const float value) {
    agi_multiplier = value;
}

void Stats::set_stam_multiplier(const float value) {
    stam_multiplier = value;
}

void Stats::set_spi_multiplier(const float value) {
    spi_multiplier = value;
}

void Stats::set_int_multiplier(const float value) {
    int_multiplier = value;
}

void Stats::increase_crit(const float value) {
    percent_crit += value;
}

void Stats::decrease_crit(const float value) {
    percent_crit -= value;
}

void Stats::increase_hit(const float value) {
    percent_hit += value;
}

void Stats::decrease_hit(const float value) {
    percent_hit -= value;
}

void Stats::increase_attack_speed(const float value) {
    percent_attack_speed += value;
}

void Stats::decrease_attack_speed(const float value) {
    percent_attack_speed -= value;
}
