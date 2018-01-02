
#include "Troll.h"

std::string Troll::get_name(void) const {
    return "Troll";
}

int Troll::get_base_strength(void) const {
    return 21;
}

int Troll::get_base_agility(void) const {
    return 22;
}

int Troll::get_base_stamina(void) const {
    return 21;
}

int Troll::get_base_intellect(void) const {
    return 16;
}

int Troll::get_base_spirit(void) const {
    return 21;
}

float Troll::get_int_multiplier() const {
    return 1.0;
}

float Troll::get_spirit_multiplier() const {
    return 1.0;
}

int Troll::get_axe_bonus() const {
    return 0;
}

int Troll::get_sword_bonus() const {
    return 0;
}

int Troll::get_mace_bonus() const {
    return 0;
}

int Troll::get_bow_bonus() const {
    return 5;
}

int Troll::get_gun_bonus() const {
    return 0;
}

int Troll::get_thrown_bonus() const {
    return 5;
}
