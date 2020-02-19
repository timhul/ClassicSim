#pragma once

#include <algorithm>

#include "math.h"

class Target;

class Mechanics {
public:
    Mechanics(Target*);

    double get_yellow_miss_chance(const unsigned wpn_skill) const;
    double get_2h_white_miss_chance(const unsigned wpn_skill) const;
    double get_dw_white_miss_chance(const unsigned wpn_skill) const;

    double get_glancing_blow_chance(const unsigned clvl) const;
    double get_dodge_chance(const unsigned wpn_skill) const;
    double get_parry_chance(const unsigned) const;
    double get_block_chance() const;

    double get_glancing_blow_dmg_penalty_min(const unsigned clvl, const unsigned wpn_skill) const;
    double get_glancing_blow_dmg_penalty_max(const unsigned clvl, const unsigned wpn_skill) const;

    double get_melee_crit_suppression(const unsigned clvl) const;
    unsigned get_suppressed_aura_crit_chance(const unsigned clvl, const unsigned crit_chance) const;

    static int get_boss_base_armor();
    static double get_reduction_from_armor(const int armor, const unsigned clvl);

    double get_spell_miss_chance_from_lvl_diff(const unsigned clvl, const double spell_hit) const;
    static double get_full_resist_chance(const unsigned t_resistance);
    static double get_partial_75_chance(const unsigned t_resistance);
    static double get_partial_50_chance(const unsigned t_resistance);
    static double get_partial_25_chance(const unsigned t_resistance);

    void set_tlvl(const int);

private:
    Target* target;

    static double get_linear_increase_in_range(const unsigned, const double, const unsigned, const double, const unsigned);
};
