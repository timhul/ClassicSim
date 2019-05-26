
#include "Troll.h"

int Troll::get_race_int() const {
    return Races::Troll;
}

QString Troll::get_name() const {
    return "Troll";
}

unsigned Troll::get_base_strength() const {
    return 21;
}

unsigned Troll::get_base_agility() const {
    return 22;
}

unsigned Troll::get_base_stamina() const {
    return 21;
}

unsigned Troll::get_base_intellect() const {
    return 16;
}

unsigned Troll::get_base_spirit() const {
    return 21;
}

double Troll::get_int_multiplier() const {
    return 1.0;
}

double Troll::get_spirit_multiplier() const {
    return 1.0;
}

unsigned Troll::get_axe_bonus() const {
    return 0;
}

unsigned Troll::get_sword_bonus() const {
    return 0;
}

unsigned Troll::get_mace_bonus() const {
    return 0;
}

unsigned Troll::get_bow_bonus() const {
    return 5;
}

unsigned Troll::get_gun_bonus() const {
    return 0;
}

unsigned Troll::get_thrown_bonus() const {
    return 5;
}
