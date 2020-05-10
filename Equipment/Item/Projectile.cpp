#include "Projectile.h"

#include <utility>

#include "Quiver.h"
#include "Weapon.h"

Projectile::Projectile(QString name,
                       int item_id,
                       Content::Phase phase,
                       int type,
                       double dps,
                       QMap<QString, QString> info,
                       QVector<QPair<QString, QString>> stats,
                       QVector<QMap<QString, QString>> procs,
                       QSet<int> mutex_item_ids) :
    Item(std::move(name), item_id, phase, nullptr, std::move(info), std::move(stats), std::move(procs), {}, {}, {}, std::move(mutex_item_ids)),
    projectile_type(type),
    dps(dps) {}

Projectile::Projectile(const Projectile* projectile) : Item(projectile) {
    this->projectile_type = projectile->projectile_type;
    this->dps = projectile->dps;
}

double Projectile::get_projectile_dps() const {
    return dps;
}

int Projectile::get_projectile_type() const {
    return projectile_type;
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

bool Projectile::valid_for_quiver(Quiver* quiver) const {
    if (quiver == nullptr)
        return true;

    switch (quiver->get_quiver_type()) {
    case QuiverTypes::QUIVER:
        return projectile_type == ProjectileTypes::ARROW;
    case QuiverTypes::AMMO_POUCH:
        return projectile_type == ProjectileTypes::BULLET;
    default:
        return false;
    }
}
