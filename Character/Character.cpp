
#include "Character.h"

Character::Character(Race* race, Engine* engine) {
    this->race = race;
    this->engine = engine;
    this->STR = race->get_base_strength();
    this->AGI = race->get_base_agility();
    this->STAM = race->get_base_stamina();
    this->INT = race->get_base_intellect();
    this->SPI = race->get_base_spirit();
    this->clvl = 1;
    this->melee_attacking = false;
}

Race* Character::get_race(void) {
    return this->race;
}

int Character::get_strength(void) {
    return STR;
}

int Character::get_agility(void) {
    return AGI;
}

int Character::get_stamina(void) {
    return STAM;
}

int Character::get_intellect(void) {
    return int(float(INT) * race->get_int_multiplier());
}

int Character::get_spirit(void) {
    return int(float(SPI) * race->get_spirit_multiplier());
}

float Character::get_hit_chance(void) const {
    return percent_hit;
}

float Character::get_crit_chance(void) const {
    return percent_crit;
}

int Character::get_clvl(void) const {
    return this->clvl;
}

void Character::set_clvl(const int& clvl) {
    this->clvl = clvl;
}

bool Character::is_dual_wielding(void) {
    return false;
}

bool Character::is_melee_attacking(void) const {
    return melee_attacking;
}

Engine* Character::get_engine(void) const {
    return this->engine;
}

void Character::start_attack(void) {
    this->melee_attacking = true;
}

void Character::stop_attack(void) {
    // TODO: Also need to clear melee hit event queues to stop next attacks landing.
    this->melee_attacking = false;
}
