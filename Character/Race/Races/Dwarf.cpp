
#include "Dwarf.h"

std::string Dwarf::get_name(void) const {
    return "Dwarf";
}

int Dwarf::get_base_strength(void) const {
    return 22;
}

int Dwarf::get_base_agility(void) const {
    return 16;
}

int Dwarf::get_base_stamina(void) const {
    return 23;
}

int Dwarf::get_base_intellect(void) const {
    return 19;
}

int Dwarf::get_base_spirit(void) const {
    return 19;
}

float Dwarf::get_int_multiplier() const {
    return 1.0;
}

float Dwarf::get_spirit_multiplier() const {
    return 1.0;
}
