#ifndef RACE_H
#define RACE_H

#include <map>
#include <QString>

class Race {
public:
    virtual ~Race() {}

    virtual QString get_name() const = 0;
    virtual int get_base_strength() const = 0;
    virtual int get_base_agility() const = 0;
    virtual int get_base_stamina() const = 0;
    virtual int get_base_intellect() const = 0;
    virtual int get_base_spirit() const = 0;
    virtual float get_int_multiplier() const = 0;
    virtual float get_spirit_multiplier() const = 0;

    virtual int get_axe_bonus() const = 0;
    virtual int get_sword_bonus() const = 0;
    virtual int get_mace_bonus() const = 0;
    virtual int get_bow_bonus() const = 0;
    virtual int get_gun_bonus() const = 0;
    virtual int get_thrown_bonus() const = 0;

protected:
    std::map<QString, int> stats;
private:
};

#endif // RACE_H
