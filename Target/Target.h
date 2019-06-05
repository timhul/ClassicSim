#ifndef TARGET_H
#define TARGET_H

#include <QMap>
#include <QString>
#include <QVector>

#include "MagicSchools.h"

class Buff;

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

    Target(int target_lvl);

    int get_lvl() const;
    void set_lvl(int);

    int get_defense() const;

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

private:
    int target_lvl;
    int target_armor;
    int base_armor;
    CreatureType target_type;
    QMap<QString, CreatureType> string_to_creature_type;
    QMap<CreatureType, QString> creature_type_strings;

    const int debuff_limit {16};
    int size_debuffs {0};
    QMap<int, QVector<Buff*>> debuffs;

    bool remove_oldest_lowest_priority_debuff(const int up_to_priority);
};

#endif // TARGET_H
