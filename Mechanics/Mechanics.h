#ifndef MECHANICS_H
#define MECHANICS_H

#include <algorithm>
#include "math.h"

class Target;

class Mechanics {
public:
    Mechanics(Target*);

    double get_yellow_miss_chance(const int wpn_skill) const;
    double get_1h_white_miss_chance(const int wpn_skill) const;
    double get_2h_white_miss_chance(const int wpn_skill) const;
    double get_dw_white_miss_chance(const int wpn_skill) const;

    double get_glancing_blow_chance(const int clvl) const;
    double get_dodge_chance(const unsigned clvl, const unsigned wpn_skill) const;
    double get_parry_chance(const int wpn_skill) const;
    double get_block_chance() const;

    double get_glancing_blow_dmg_penalty(const int wpn_skill) const;
    double get_linear_glancing_blow_dmg_penalty(const int wpn_skill) const;

    static int get_boss_base_armor();
    static double get_reduction_from_armor(const int armor, const int clvl);

    double get_spell_miss_chance_from_lvl_diff(const int clvl, const double spell_hit) const;
    static double get_full_resist_chance(const int t_resistance);
    static double get_partial_75_chance(const int t_resistance);
    static double get_partial_50_chance(const int t_resistance);
    static double get_partial_25_chance(const int t_resistance);

    void set_tlvl(const int);

private:
    Target* target;

    static double get_linear_increase_in_range(const int, const double, const int, const double, const int);
};

#endif // MECHANICS_H
