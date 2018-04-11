#ifndef MAINHAND_H
#define MAINHAND_H

#include "MeleeWeapon.h"

class Mainhand: public MeleeWeapon {
public:
    Mainhand(QString name, int type, int min, int max, float speed, QVector<QPair<QString, QString>> stats = {}, QMap<QString, QString> info = {}):
        MeleeWeapon(name, type, min, max, speed, stats, info) {}

    int get_item_type() const override;
    int get_weapon_slot() const override;

protected:
private:
};

#endif // MAINHAND_H
