#ifndef MAINHAND_H
#define MAINHAND_H

#include "Weapon.h"

class Mainhand: public Weapon {
public:
    Mainhand(QString name, int type, unsigned min, unsigned max, double speed,
             QVector<QPair<QString, QString>> stats = {},
             QMap<QString, QString> info = {},
             QVector<QMap<QString, QString>> procs = {}):
        Weapon(name, type, min, max, speed, stats, info, procs) {}
    Mainhand(const Mainhand* mh):
        Weapon(mh) {}

    int get_item_slot() const override;
    int get_weapon_slot() const override;

protected:
private:
};

#endif // MAINHAND_H
