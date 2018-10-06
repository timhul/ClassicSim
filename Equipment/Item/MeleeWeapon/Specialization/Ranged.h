#ifndef RANGED_H
#define RANGED_H

#include "Weapon.h"

class Ranged: public Weapon {
public:
    Ranged(QString name, int type, unsigned min, unsigned max, double speed,
           QVector<QPair<QString, QString>> stats = {},
           QMap<QString, QString> info = {},
           QVector<QMap<QString, QString>> procs = {}):
        Weapon(name, type, min, max, speed, stats, info, procs) {}
    Ranged(const Ranged* ranged):
        Weapon(ranged) {}

    int get_item_slot() const override;
    int get_weapon_slot() const override;

protected:
private:
};

#endif // RANGED_H
