
#include "Weapon.h"

Weapon::Weapon(QString name, int type, int min, int max, double speed,
       QVector<QPair<QString, QString>> stats,
       QMap<QString, QString> info,
       QVector<QMap<QString, QString>> procs):
    Item(name, stats, info, procs) {
    this->random = new Random(min, max);
    this->weapon_type = type;
    this->min_dmg = min;
    this->max_dmg = max;
    this->weapon_speed = speed;
}

Weapon::~Weapon() {
    delete random;
}

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

double Weapon::get_base_weapon_speed() const {
    return weapon_speed;
}

double Weapon::get_wpn_dps() const {
    return ((min_dmg + max_dmg) / 2) / weapon_speed;
}
