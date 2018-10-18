#ifndef WEAPON_H
#define WEAPON_H

#include <QVector>

#include "Item.h"
#include "Random.h"

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
    bool is_2hand() const;

    bool has_temporary_enchant() const;
    void apply_enchant(EnchantName::Name enchant_name, Character* pchar, const bool mainhand);
    void apply_temporary_enchant(EnchantName::Name enchant_name, Character* pchar, const bool mainhand);
    void clear_temporary_enchant();
    void clear_windfury();
    QString get_temporary_enchant_name() const;
    QString get_temporary_enchant_effect() const;
    EnchantName::Name get_temporary_enchant_enum_value() const;

private:
    Random* random;
    int weapon_type;
    int weapon_slot;
    unsigned min_dmg;
    unsigned max_dmg;
    double weapon_speed;
    Enchant* temporary_enchant;
};

#endif // WEAPON_H
