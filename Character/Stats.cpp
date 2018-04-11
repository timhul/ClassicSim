
#include "Stats.h"
#include "Character.h"
#include "Race.h"
#include <QDebug>

Stats::Stats(QObject* parent ) :
    QObject(parent)
{
    this->percent_hit = 0.0;
    this->percent_crit = 0.0;
    this->percent_attack_speed = 0.0;
    this->STR = 0;
    this->AGI = 0;
    this->STAM = 0;
    this->INT = 0;
    this->SPI = 0;
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

int Stats::get_strength(void) {
    return STR;
}

int Stats::get_agility(void) {
    return AGI;
}

int Stats::get_stamina(void) {
    return STAM;
}

int Stats::get_intellect(void) {
    return int(float(INT) * int_multiplier);
}

int Stats::get_spirit(void) {
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

int Stats::get_melee_ap_str_excluded() {
    return melee_ap;
}

int Stats::get_melee_ap_total() {
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
