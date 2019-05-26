
#include "Gnome.h"

int Gnome::get_race_int() const {
    return Races::Gnome;
}

QString Gnome::get_name() const {
    return "Gnome";
}

unsigned Gnome::get_base_strength() const {
    return 15;
}

unsigned Gnome::get_base_agility() const {
    return 23;
}

unsigned Gnome::get_base_stamina() const {
    return 19;
}

unsigned Gnome::get_base_intellect() const {
    return 23;
}

unsigned Gnome::get_base_spirit() const {
    return 20;
}

double Gnome::get_int_multiplier() const {
    return 1.05;
}

double Gnome::get_spirit_multiplier() const {
    return 1.0;
}

unsigned Gnome::get_axe_bonus() const {
    return 0;
}

unsigned Gnome::get_sword_bonus() const {
    return 0;
}

unsigned Gnome::get_mace_bonus() const {
    return 0;
}

unsigned Gnome::get_bow_bonus() const {
    return 0;
}

unsigned Gnome::get_gun_bonus() const {
    return 0;
}

unsigned Gnome::get_thrown_bonus() const {
    return 0;
}
