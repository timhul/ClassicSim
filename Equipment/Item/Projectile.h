#pragma once

#include <QVector>

#include "Item.h"

class Weapon;

class Projectile: public Item {
public:
    Projectile(QString name, int item_id, Content::Phase phase, int type, double dps,
               QMap<QString, QString> info = {},
               QVector<QPair<QString, QString>> stats = {},
               QVector<QMap<QString, QString>> procs = {},
               QSet<int> mutex_item_ids = {});
    Projectile(const Projectile* projectile);

    double get_projectile_dps() const;
    bool valid_for_weapon(Weapon* weapon) const;

private:
    int projectile_type;
    double dps;
};
