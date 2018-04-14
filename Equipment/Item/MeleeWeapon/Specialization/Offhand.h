#ifndef OFFHAND_H
#define OFFHAND_H

#include "Weapon.h"

class Offhand: public Weapon {
public:
    Offhand(QString name, int type, int min, int max, float speed, QVector<QPair<QString, QString>> stats = {}, QMap<QString, QString> info = {}):
        Weapon(name, type, min, max, speed, stats, info) {}

    int get_item_slot() const override;
    int get_weapon_slot() const override;

protected:
private:
};

#endif // OFFHAND_H
