#ifndef MECHANICS_H
#define MECHANICS_H

#include <algorithm>
#include "math.h"

class Target;

class Mechanics {
public:
    Mechanics(Target*);

    double get_yellow_miss_chance(const int) const;
    double get_1h_white_miss_chance(const int) const;
    double get_2h_white_miss_chance(const int) const;
    double get_dw_white_miss_chance(const int) const;

    double get_glancing_blow_chance(const int) const;
    double get_dodge_chance(const int) const;
    double get_parry_chance(const int) const;
    double get_block_chance(void) const;

    double get_glancing_blow_dmg_penalty(const int) const;

    int get_boss_base_armor() const;
    double get_reduction_from_armor(const int armor, const int clvl) const;

    void set_tlvl(const int);
protected:
private:
    Target* target;
};

#endif // MECHANICS_H
