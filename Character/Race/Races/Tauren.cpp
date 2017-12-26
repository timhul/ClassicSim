
#include "Tauren.h"

std::string Tauren::get_name(void) const {
    return "Tauren";
}

int Tauren::get_base_strength(void) const {
    return 25;
}

int Tauren::get_base_agility(void) const {
    return 15;
}

int Tauren::get_base_stamina(void) const {
    return 22;
}

int Tauren::get_base_intellect(void) const {
    return 15;
}

int Tauren::get_base_spirit(void) const {
    return 22;
}

float Tauren::get_int_multiplier() const {
    return 1.0;
}

float Tauren::get_spirit_multiplier() const {
    return 1.0;
}
