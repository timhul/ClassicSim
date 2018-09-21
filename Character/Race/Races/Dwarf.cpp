
#include "Dwarf.h"

int Dwarf::get_race_int() const {
    return Races::Dwarf;
}

QString Dwarf::get_name(void) const {
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

double Dwarf::get_int_multiplier() const {
    return 1.0;
}

double Dwarf::get_spirit_multiplier() const {
    return 1.0;
}

int Dwarf::get_axe_bonus() const {
    return 0;
}

int Dwarf::get_sword_bonus() const {
    return 0;
}

int Dwarf::get_mace_bonus() const {
    return 0;
}

int Dwarf::get_bow_bonus() const {
    return 0;
}

int Dwarf::get_gun_bonus() const {
    return 5;
}

int Dwarf::get_thrown_bonus() const {
    return 0;
}
