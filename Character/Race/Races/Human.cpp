
#include "Human.h"

std::string Human::get_name(void) const {
    return "Human";
}

int Human::get_base_strength(void) const {
    return 20;
}

int Human::get_base_agility(void) const {
    return 20;
}

int Human::get_base_stamina(void) const {
    return 20;
}

int Human::get_base_intellect(void) const {
    return 20;
}

int Human::get_base_spirit(void) const {
    return 20;
}

float Human::get_int_multiplier() const {
    return 1.0;
}

float Human::get_spirit_multiplier() const {
    return 1.05;
}
