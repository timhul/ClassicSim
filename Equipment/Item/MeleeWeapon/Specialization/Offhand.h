#ifndef OFFHAND_H
#define OFFHAND_H

#include "Weapon.h"

class Offhand: public Weapon {
public:
    Offhand(QString name, int type, unsigned min, unsigned max, double speed,
            QVector<QPair<QString, QString>> stats = {},
            QMap<QString, QString> info = {},
            QVector<QMap<QString, QString>> procs = {}):
        Weapon(name, type, min, max, speed, stats, info, procs) {}

    int get_item_slot() const override;
    int get_weapon_slot() const override;

protected:
private:
};

#endif // OFFHAND_H
