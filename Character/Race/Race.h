#ifndef RACE_H
#define RACE_H

#include <QString>

namespace Races {
    static const int Dwarf = 0;
    static const int Gnome = 1;
    static const int Human = 2;
    static const int NightElf = 3;
    static const int Orc = 4;
    static const int Tauren = 5;
    static const int Troll = 6;
    static const int Undead = 7;
}

class Race {
public:
    virtual ~Race();

    virtual int get_race_int() const = 0;
    virtual QString get_name() const = 0;
    virtual unsigned get_base_strength() const = 0;
    virtual unsigned get_base_agility() const = 0;
    virtual unsigned get_base_stamina() const = 0;
    virtual unsigned get_base_intellect() const = 0;
    virtual unsigned get_base_spirit() const = 0;
    virtual double get_int_multiplier() const = 0;
    virtual double get_spirit_multiplier() const = 0;

    virtual unsigned get_axe_bonus() const = 0;
    virtual unsigned get_sword_bonus() const = 0;
    virtual unsigned get_mace_bonus() const = 0;
    virtual unsigned get_bow_bonus() const = 0;
    virtual unsigned get_gun_bonus() const = 0;
    virtual unsigned get_thrown_bonus() const = 0;
};

#endif // RACE_H
