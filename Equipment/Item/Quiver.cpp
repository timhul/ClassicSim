#include "Quiver.h"

#include "Projectile.h"
#include "Weapon.h"

Quiver::Quiver(QString name,
               int item_id,
               Content::Phase phase,
               QMap<QString, QString> info,
               QVector<QPair<QString, QString>> stats,
               QVector<QMap<QString, QString>> procs,
               QSet<int> mutex_item_ids) :
    Item(std::move(name), item_id, phase, nullptr, std::move(info), std::move(stats), std::move(procs), {}, {}, {}, std::move(mutex_item_ids)) {}

Quiver::Quiver(const Quiver* quiver) : Item(quiver) {}

bool Quiver::valid_for_weapon(Weapon* weapon) const {
    if (weapon == nullptr)
        return true;

    switch (weapon->get_weapon_type()) {
    case WeaponTypes::BOW:
    case WeaponTypes::CROSSBOW:
        return get_item_type() == QuiverTypes::QUIVER;
    case WeaponTypes::GUN:
        return get_item_type() == QuiverTypes::AMMO_POUCH;
    default:
        return false;
    }
}

bool Quiver::valid_for_projectile(Projectile* projectile) const {
    if (projectile == nullptr)
        return true;

    switch (projectile->get_projectile_type()) {
    case ProjectileTypes::ARROW:
        return get_item_type() == QuiverTypes::QUIVER;
    case ProjectileTypes::BULLET:
        return get_item_type() == QuiverTypes::AMMO_POUCH;
    default:
        return false;
    }
}

int Quiver::get_quiver_type() const {
    return get_item_type();
}
