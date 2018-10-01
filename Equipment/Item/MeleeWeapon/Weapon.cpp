
#include "Weapon.h"

#include <utility>

Weapon::Weapon(QString name, int type, unsigned min, unsigned max, double speed,
       QVector<QPair<QString, QString>> stats,
       QMap<QString, QString> info,
       QVector<QMap<QString, QString>> procs):
    Item(std::move(name), std::move(stats), std::move(info), std::move(procs)) {
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

unsigned Weapon::get_min_dmg() const {
    return min_dmg;
}

unsigned Weapon::get_max_dmg() const {
    return max_dmg;
}

unsigned Weapon::get_random_dmg() const {
    const unsigned roll = random->get_roll();
    assert(roll >= min_dmg);
    assert(roll <= max_dmg);
    return roll;
}

double Weapon::get_base_weapon_speed() const {
    return weapon_speed;
}

double Weapon::get_wpn_dps() const {
    return (double(min_dmg + max_dmg) / 2) / weapon_speed;
}
