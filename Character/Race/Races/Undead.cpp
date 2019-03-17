
#include "Undead.h"

int Undead::get_race_int() const {
    return Races::Undead;
}

QString Undead::get_name() const {
    return "Undead";
}

unsigned Undead::get_base_strength() const {
    return 19;
}

unsigned Undead::get_base_agility() const {
    return 18;
}

unsigned Undead::get_base_stamina() const {
    return 21;
}

unsigned Undead::get_base_intellect() const {
    return 18;
}

unsigned Undead::get_base_spirit() const {
    return 25;
}

double Undead::get_int_multiplier() const {
    return 1.0;
}

double Undead::get_spirit_multiplier() const {
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
