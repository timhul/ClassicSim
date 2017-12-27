
#include "Character.h"

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
