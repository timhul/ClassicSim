#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QVector>

#include "Item.h"

class Weapon;

class Projectile: public Item {
public:
    Projectile(QString name, int item_id, int type, double dps,
               QMap<QString, QString> info = {},
               QVector<QPair<QString, QString>> stats = {},
               QVector<QMap<QString, QString>> procs = {});
    Projectile(const Projectile* projectile);

    int get_projectile_type() const;
    double get_projectile_dps() const;
    QString get_projectile_type_string() const;
    bool valid_for_weapon(Weapon* weapon) const;

private:
    int projectile_type;
    double dps;
};

#endif // PROJECTILE_H
