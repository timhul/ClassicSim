#ifndef ONEHAND_H
#define ONEHAND_H

#include "MeleeWeapon.h"

class Onehand: public MeleeWeapon {
public:
    Onehand(QString name, int type, int min, int max, float speed, QVector<QPair<QString, QString>> stats = {}, QMap<QString, QString> info = {}):
        MeleeWeapon(name, type, min, max, speed, stats, info) {}

    int get_item_type() const override;
    int get_weapon_slot() const override;

protected:
private:
};

#endif // ONEHAND_H
