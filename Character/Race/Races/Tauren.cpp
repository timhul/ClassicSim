
#include "Tauren.h"

int Tauren::get_race_int() const {
    return Races::Tauren;
}

QString Tauren::get_name() const {
    return "Tauren";
}

unsigned Tauren::get_base_strength() const {
    return 25;
}

unsigned Tauren::get_base_agility() const {
    return 15;
}

unsigned Tauren::get_base_stamina() const {
    return 22;
}

unsigned Tauren::get_base_intellect() const {
    return 15;
}

unsigned Tauren::get_base_spirit() const {
    return 22;
}

double Tauren::get_int_multiplier() const {
    return 1.0;
}

double Tauren::get_spirit_multiplier() const {
    return 1.0;
}

int Tauren::get_axe_bonus() const {
    return 0;
}

int Tauren::get_sword_bonus() const {
    return 0;
}

int Tauren::get_mace_bonus() const {
    return 0;
}

int Tauren::get_bow_bonus() const {
    return 0;
}

int Tauren::get_gun_bonus() const {
    return 0;
}

int Tauren::get_thrown_bonus() const {
    return 0;
}
