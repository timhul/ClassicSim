
#include "Dwarf.h"

int Dwarf::get_race_int() const {
    return Races::Dwarf;
}

QString Dwarf::get_name() const {
    return "Dwarf";
}

unsigned Dwarf::get_base_strength() const {
    return 22;
}

unsigned Dwarf::get_base_agility() const {
    return 16;
}

unsigned Dwarf::get_base_stamina() const {
    return 23;
}

unsigned Dwarf::get_base_intellect() const {
    return 19;
}

unsigned Dwarf::get_base_spirit() const {
    return 19;
}

double Dwarf::get_int_multiplier() const {
    return 1.0;
}

double Dwarf::get_spirit_multiplier() const {
    return 1.0;
}

unsigned Dwarf::get_axe_bonus() const {
    return 0;
}

unsigned Dwarf::get_sword_bonus() const {
    return 0;
}

unsigned Dwarf::get_mace_bonus() const {
    return 0;
}

unsigned Dwarf::get_bow_bonus() const {
    return 0;
}

unsigned Dwarf::get_gun_bonus() const {
    return 5;
}

unsigned Dwarf::get_thrown_bonus() const {
    return 0;
}
