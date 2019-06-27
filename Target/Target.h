#pragma once

#include <QMap>
#include <QString>
#include <QVector>

#include "MagicSchools.h"

class Buff;
class Stats;

class Target {
public:
    enum CreatureType {
        Beast = 0,
        Demon,
        Dragonkin,
        Elemental,
        Giant,
        Humanoid,
        Mechanical,
        Undead
    };

    Target(const unsigned target_lvl);
    ~Target();

    Stats* get_stats() const;

    unsigned get_lvl() const;
    void set_lvl(const unsigned);

    unsigned get_defense() const;

    int get_armor() const;
    void increase_armor(const int);
    void decrease_armor(const int);

    int get_base_armor() const;
    void set_base_armor(const int);

    int get_resistance(const MagicSchool school) const;

    CreatureType get_creature_type() const;
    QString get_creature_type_string() const;
    void set_creature_type(const QString& target);

    bool add_debuff(Buff* buff, const int priority);
    void remove_debuff(Buff* buff);
    void reset();

    double get_magic_school_damage_mod(const MagicSchool school) const;
    void increase_magic_school_damage_mod(const int increase, const MagicSchool school, Buff* buff = nullptr);
    void decrease_magic_school_damage_mod(const int decrease, const MagicSchool school, Buff* buff = nullptr);

private:
    unsigned target_lvl;
    int base_armor;
    CreatureType target_type;
    Stats* stats;
    QMap<QString, CreatureType> string_to_creature_type;
    QMap<CreatureType, QString> creature_type_strings;
    QMap<MagicSchool, QVector<int>> magic_school_damage_changes;
    QMap<MagicSchool, double> magic_school_damage_modifiers;
    QMap<MagicSchool, QVector<Buff*>> magic_school_buffs_with_charges;

    const int debuff_limit {16};
    int size_debuffs {0};
    QMap<int, QVector<Buff*>> debuffs;

    bool remove_oldest_lowest_priority_debuff(const int up_to_priority);
};
