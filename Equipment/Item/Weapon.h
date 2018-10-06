#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
#include "Random.h"
#include <QVector>

class Weapon: public Item {
public:
    Weapon(QString name, int type, int weapon_slot, unsigned min, unsigned max, double speed,
           QVector<QPair<QString, QString>> stats = {},
           QMap<QString, QString> info = {},
           QVector<QMap<QString, QString>> procs = {});
    Weapon(const Weapon* weapon);

    virtual ~Weapon() override;

    int get_weapon_slot() const override;
    int get_weapon_type() const;
    unsigned get_min_dmg() const;
    unsigned get_max_dmg() const;
    unsigned get_random_dmg() const;
    double get_base_weapon_speed() const;
    double get_wpn_dps() const;
    QString get_weapon_type_string() const;

protected:
    Random* random;
    int weapon_type;
    int weapon_slot;
    unsigned min_dmg;
    unsigned max_dmg;
    double weapon_speed;
private:
};

#endif // WEAPON_H
