
#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(int type, int min, int max, float speed, float proc_rate) {
    this->weapon_type = type;
    this->min_dmg = min;
    this->max_dmg = max;
    this->weapon_speed = speed;
    this->proc_rate = proc_rate;
}

int MeleeWeapon::get_weapon_type() const {
    return weapon_type;
}

int MeleeWeapon::get_min_dmg() const {
    return min_dmg;
}

int MeleeWeapon::get_max_dmg() const {
    return max_dmg;
}

float MeleeWeapon::get_base_weapon_speed() const {
    return weapon_speed;
}

float MeleeWeapon::get_weapon_proc_rate() const {
    return proc_rate;
}
