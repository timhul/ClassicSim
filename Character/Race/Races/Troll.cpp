
#include "Troll.h"

int Troll::get_race_int() const {
    return Races::Troll;
}

QString Troll::get_name() const {
    return "Troll";
}

int Troll::get_base_strength() const {
    return 21;
}

int Troll::get_base_agility() const {
    return 22;
}

int Troll::get_base_stamina() const {
    return 21;
}

int Troll::get_base_intellect() const {
    return 16;
}

int Troll::get_base_spirit() const {
    return 21;
}

double Troll::get_int_multiplier() const {
    return 1.0;
}

double Troll::get_spirit_multiplier() const {
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
