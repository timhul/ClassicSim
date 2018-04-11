
#include "MeleeWeapon.h"

int MeleeWeapon::get_weapon_type() const {
    return weapon_type;
}

int MeleeWeapon::get_min_dmg() const {
    return min_dmg;
}

int MeleeWeapon::get_max_dmg() const {
    return max_dmg;
}

int MeleeWeapon::get_random_dmg() const {
    const int roll = random->get_roll();
    assert(roll >= get_min_dmg());
    assert(roll <= get_max_dmg());
    return roll;
}

float MeleeWeapon::get_base_weapon_speed() const {
    return weapon_speed;
}
