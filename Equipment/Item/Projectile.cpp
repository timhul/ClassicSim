#include "Projectile.h"

#include <utility>

#include "Weapon.h"

Projectile::Projectile(QString name, int item_id, int type, double dps,
                       QMap<QString, QString> info,
                       QVector<QPair<QString, QString> > stats,
                       QVector<QMap<QString, QString>> procs):
    Item(std::move(name), item_id, std::move(info), std::move(stats), std::move(procs)),
    projectile_type(type),
    dps(dps)
{}

Projectile::Projectile(const Projectile* projectile):
    Item(projectile)
{
    this->projectile_type = projectile->projectile_type;
    this->dps = projectile->dps;
}

int Projectile::get_projectile_type() const {
    return projectile_type;
}

double Projectile::get_projectile_dps() const {
    return dps;
}

QString Projectile::get_projectile_type_string() const {
    switch (projectile_type) {
    case ProjectileTypes::ARROW:
        return "Arrow";
    case ProjectileTypes::BULLET:
        return "Bullet";
    default:
        return "Unknown";
    }
}

bool Projectile::valid_for_weapon(Weapon* weapon) const {
    if (weapon == nullptr)
        return true;

    switch (weapon->get_weapon_type()) {
    case WeaponTypes::BOW:
    case WeaponTypes::CROSSBOW:
        return projectile_type == ProjectileTypes::ARROW ? true : false;
    case WeaponTypes::GUN:
        return projectile_type == ProjectileTypes::BULLET ? true : false;
    default:
        return false;
    }
}
