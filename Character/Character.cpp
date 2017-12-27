
#include "Character.h"

Character::Character(Race* race) {
    this->race = race;
    this->STR = race->get_base_strength();
    this->AGI = race->get_base_agility();
    this->STAM = race->get_base_stamina();
    this->INT = race->get_base_intellect();
    this->SPI = race->get_base_spirit();
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
