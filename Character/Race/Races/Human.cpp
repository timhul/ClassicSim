
#include "Human.h"

int Human::get_race_int() const {
    return Races::Human;
}

QString Human::get_name() const {
    return "Human";
}

unsigned Human::get_base_strength() const {
    return 20;
}

unsigned Human::get_base_agility() const {
    return 20;
}

unsigned Human::get_base_stamina() const {
    return 20;
}

unsigned Human::get_base_intellect() const {
    return 20;
}

unsigned Human::get_base_spirit() const {
    return 20;
}

double Human::get_int_multiplier() const {
    return 1.0;
}

double Human::get_spirit_multiplier() const {
    return 1.05;
}

int Human::get_axe_bonus() const {
    return 0;
}

int Human::get_sword_bonus() const {
    return 5;
}

int Human::get_mace_bonus() const {
    return 5;
}

int Human::get_bow_bonus() const {
    return 0;
}

int Human::get_gun_bonus() const {
    return 0;
}

int Human::get_thrown_bonus() const {
    return 0;
}
