
#include "Gnome.h"

std::string Gnome::get_name(void) const {
    return "Gnome";
}

int Gnome::get_base_strength(void) const {
    return 15;
}

int Gnome::get_base_agility(void) const {
    return 23;
}

int Gnome::get_base_stamina(void) const {
    return 19;
}

int Gnome::get_base_intellect(void) const {
    return 23;
}

int Gnome::get_base_spirit(void) const {
    return 20;
}

float Gnome::get_int_multiplier() const {
    return 1.05;
}

float Gnome::get_spirit_multiplier() const {
    return 1.0;
}

int Gnome::get_axe_bonus() const {
    return 0;
}

int Gnome::get_sword_bonus() const {
    return 0;
}

int Gnome::get_mace_bonus() const {
    return 0;
}

int Gnome::get_bow_bonus() const {
    return 0;
}

int Gnome::get_gun_bonus() const {
    return 0;
}

int Gnome::get_thrown_bonus() const {
    return 0;
}
