#pragma once

#include "Item.h"

class Weapon;
class Projectile;

class Quiver : public Item
{
public:
    Quiver(QString name, int item_id, Content::Phase phase,
               QMap<QString, QString> info = {},
               QVector<QPair<QString, QString>> stats = {},
               QVector<QMap<QString, QString>> procs = {},
               QSet<int> mutex_item_ids = {});
    Quiver(const Quiver* quiver);

    bool valid_for_weapon(Weapon* weapon) const;
    bool valid_for_projectile(Projectile* projectile) const;

    int get_quiver_type() const;
};

