
#include "Character.h"

Character::Character(Race* race, Engine* engine, Equipment* equipment) {
    this->race = race;
    this->engine = engine;
    this->equipment = equipment;
    this->STR = race->get_base_strength();
    this->AGI = race->get_base_agility();
    this->STAM = race->get_base_stamina();
    this->INT = race->get_base_intellect();
    this->SPI = race->get_base_spirit();
    this->clvl = 1;
    this->melee_attacking = false;
    this->last_action = 0 - this->global_cooldown();
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

Equipment* Character::get_equipment(void) const {
    return this->equipment;
}

void Character::start_attack(void) {
    this->melee_attacking = true;
}

void Character::stop_attack(void) {
    // TODO: Also need to clear melee hit event queues to stop next attacks landing.
    this->melee_attacking = false;
}

float Character::global_cooldown() const {
    return 1.5;
}

bool Character::action_ready() const {
    // Allow some rounding errors (this could effectively speed up gcd by 1/10000ths of a second).
    float delta = last_action + global_cooldown() - engine->get_current_priority();
    return delta < 0.0001;
}
