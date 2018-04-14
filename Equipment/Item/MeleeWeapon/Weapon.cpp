
#include "Weapon.h"

int Weapon::get_weapon_type() const {
    return weapon_type;
}

int Weapon::get_min_dmg() const {
    return min_dmg;
}

int Weapon::get_max_dmg() const {
    return max_dmg;
}

int Weapon::get_random_dmg() const {
    const int roll = random->get_roll();
    assert(roll >= get_min_dmg());
    assert(roll <= get_max_dmg());
    return roll;
}

float Weapon::get_base_weapon_speed() const {
    return weapon_speed;
}

float Weapon::get_wpn_dps() const {
    return ((min_dmg + max_dmg) / 2) / weapon_speed;
}
