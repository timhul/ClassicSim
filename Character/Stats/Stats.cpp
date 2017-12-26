
#include "Stats.h"

Stats::Stats(Race* race) {
    this->race = race;
    this->STR = race->get_base_strength();
    this->AGI = race->get_base_agility();
    this->STAM = race->get_base_stamina();
    this->INT = race->get_base_intellect();
    this->SPI = race->get_base_spirit();
}

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
    return int(float(INT) * race->get_int_multiplier());
}

int Stats::get_spirit(void) {
    return int(float(SPI) * race->get_spirit_multiplier());
}
