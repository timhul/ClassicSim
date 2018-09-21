#ifndef MAINHAND_H
#define MAINHAND_H

#include "Weapon.h"

class Mainhand: public Weapon {
public:
    Mainhand(QString name, int type, int min, int max, double speed,
             QVector<QPair<QString, QString>> stats = {},
             QMap<QString, QString> info = {},
             QVector<QMap<QString, QString>> procs = {}):
        Weapon(name, type, min, max, speed, stats, info, procs) {}

    int get_item_slot() const override;
    int get_weapon_slot() const override;

protected:
private:
};

#endif // MAINHAND_H
