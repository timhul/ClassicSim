
#include "Undead.h"

QString Undead::get_name(void) const {
    return "Undead";
}

int Undead::get_base_strength(void) const {
    return 19;
}

int Undead::get_base_agility(void) const {
    return 18;
}

int Undead::get_base_stamina(void) const {
    return 21;
}

int Undead::get_base_intellect(void) const {
    return 18;
}

int Undead::get_base_spirit(void) const {
    return 25;
}

float Undead::get_int_multiplier() const {
    return 1.0;
}

float Undead::get_spirit_multiplier() const {
    return 1.0;
}

int Undead::get_axe_bonus() const {
    return 0;
}

int Undead::get_sword_bonus() const {
    return 0;
}

int Undead::get_mace_bonus() const {
    return 0;
}

int Undead::get_bow_bonus() const {
    return 0;
}

int Undead::get_gun_bonus() const {
    return 0;
}

int Undead::get_thrown_bonus() const {
    return 0;
}
