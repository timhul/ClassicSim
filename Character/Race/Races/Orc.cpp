
#include "Orc.h"

int Orc::get_race_int() const {
    return Races::Orc;
}

QString Orc::get_name(void) const {
    return "Orc";
}

int Orc::get_base_strength(void) const {
    return 23;
}

int Orc::get_base_agility(void) const {
    return 17;
}

int Orc::get_base_stamina(void) const {
    return 22;
}

int Orc::get_base_intellect(void) const {
    return 17;
}

int Orc::get_base_spirit(void) const {
    return 23;
}

float Orc::get_int_multiplier() const {
    return 1.0;
}

float Orc::get_spirit_multiplier() const {
    return 1.0;
}

int Orc::get_axe_bonus() const {
    return 5;
}

int Orc::get_sword_bonus() const {
    return 0;
}

int Orc::get_mace_bonus() const {
    return 0;
}

int Orc::get_bow_bonus() const {
    return 0;
}

int Orc::get_gun_bonus() const {
    return 0;
}

int Orc::get_thrown_bonus() const {
    return 0;
}
