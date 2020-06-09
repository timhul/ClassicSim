#include "Mechanics.h"

#include "Target.h"
#include "Utils/Check.h"

Mechanics::Mechanics(Target* target) : target(target) {}

double Mechanics::get_yellow_miss_chance(const unsigned wpn_skill) const {
    return get_2h_white_miss_chance(wpn_skill);
}

double Mechanics::get_dw_white_miss_chance(const unsigned wpn_skill) const {
    return get_2h_white_miss_chance(wpn_skill) * 0.8 + 0.2;
}

double Mechanics::get_2h_white_miss_chance(const unsigned wpn_skill) const {
    const int t_defense_to_p_wpn_skill = static_cast<int>(target->get_defense()) - static_cast<int>(wpn_skill);

    if (t_defense_to_p_wpn_skill > 10)
        return 0.05 + 0.01 + t_defense_to_p_wpn_skill * 0.002;

    return 0.05 + t_defense_to_p_wpn_skill * 0.001;
}

double Mechanics::get_glancing_blow_chance(const unsigned clvl) const {
    // Non-melee classes do not follow this formula.
    const int level_diff = static_cast<int>(target->get_lvl()) - static_cast<int>(clvl);
    if (level_diff < 0)
        return 0.0;

    return 0.1 + level_diff * 5 * 0.02;
}

double Mechanics::get_dodge_chance(const unsigned wpn_skill) const {
    // https://us.forums.blizzard.com/en/wow/t/bug-hit-tables/185675/12
    // "Creatures at your level have a 5% chance to Dodge your attacks. Each additional
    // level the target has over the player grants them 0.5% additional chance to dodge.""

    // Further, according to testing described in https://github.com/magey/classic-warrior/wiki/Attack-table#dodge
    // weapon skill counters this difference slightly.
    const int defense_diff = static_cast<int>(target->get_defense()) - static_cast<int>(wpn_skill);

    return std::max(0.0, 0.05 + defense_diff * 0.001);
}

double Mechanics::get_parry_chance(const unsigned wpn_skill) const {
    const int defense_diff = static_cast<int>(target->get_defense()) - static_cast<int>(wpn_skill);
    return std::max(0.0, 0.14 + defense_diff * 0.001);
}

double Mechanics::get_block_chance() const {
    return 0.0;
}

double Mechanics::get_glancing_blow_dmg_penalty_min(const unsigned clvl, const unsigned wpn_skill) const {
    const int level_diff = static_cast<int>(target->get_lvl()) - static_cast<int>(clvl);
    if (level_diff < 1)
        return 1.0;

    const int t_defense_to_p_wpn_skill = static_cast<int>(target->get_defense()) - static_cast<int>(wpn_skill);
    const double glance_max_range_penalty = 1.3 - 0.05 * t_defense_to_p_wpn_skill;

    if (glance_max_range_penalty < 0.55)
        return 0.55;
    if (glance_max_range_penalty > 0.91)
        return 0.91;

    return glance_max_range_penalty;
}

double Mechanics::get_glancing_blow_dmg_penalty_max(const unsigned clvl, const unsigned wpn_skill) const {
    const int level_diff = static_cast<int>(target->get_lvl()) - static_cast<int>(clvl);
    if (level_diff < 1)
        return 1.0;

    const int t_defense_to_p_wpn_skill = static_cast<int>(target->get_defense()) - static_cast<int>(wpn_skill);
    const double glance_max_range_penalty = 1.2 - 0.03 * t_defense_to_p_wpn_skill;

    if (glance_max_range_penalty < 0.75)
        return 0.75;
    if (glance_max_range_penalty > 0.99)
        return 0.99;

    return glance_max_range_penalty;
}

int Mechanics::get_boss_base_armor() {
    return 3750;
}

double Mechanics::get_reduction_from_armor(const int armor, const unsigned clvl) {
    return static_cast<double>(armor) / (static_cast<double>(armor) + 400 + 85 * clvl);
}

double Mechanics::get_melee_crit_suppression(const unsigned clvl) const {
    const int level_diff = static_cast<int>(target->get_lvl()) - static_cast<int>(clvl);

    return std::max(0.0, 0.01 * level_diff);
}

unsigned Mechanics::get_suppressed_aura_crit_chance(const unsigned clvl, const unsigned aura_crit) const {
    const int level_diff = static_cast<int>(target->get_lvl()) - static_cast<int>(clvl);

    if (level_diff <= 0)
        return aura_crit;

    const unsigned penalty = 60 * static_cast<unsigned>(level_diff);

    return aura_crit > penalty ? aura_crit - penalty : 0;
}

double Mechanics::get_spell_miss_chance_from_lvl_diff(const unsigned clvl, const double spell_hit) const {
    const int level_diff = static_cast<int>(target->get_lvl()) - static_cast<int>(clvl);

    if (level_diff < -2)
        return 0.01;

    double lvl_diff_penalty;
    switch (level_diff) {
    case -2:
        lvl_diff_penalty = 0.02;
        break;
    case -1:
        lvl_diff_penalty = 0.03;
        break;
    case 0:
        lvl_diff_penalty = 0.04;
        break;
    case 1:
        lvl_diff_penalty = 0.05;
        break;
    case 2:
        lvl_diff_penalty = 0.06;
        break;
    case 3:
        lvl_diff_penalty = 0.17;
        break;
    case 4:
        lvl_diff_penalty = 0.28;
        break;
    default:
        lvl_diff_penalty = 0.39;
        break;
    }

    return std::max(0.01, lvl_diff_penalty - spell_hit);
}

double Mechanics::get_full_resist_chance(const unsigned t_resistance) {
    // Piecewise-linear function that implements the following resistance table:
    //
    // Target resistance | 0-150 | 150-200 | 200-300 |
    // % Occurance       | 0-1 % |  1-4 %  |  4-25 % |
    //
    // This formula only serves as an initial approximation and is likely incorrect.
    if (t_resistance < 150)
        return get_linear_increase_in_range(0, 0.0, 150, 0.01, t_resistance);

    if (t_resistance < 200)
        return get_linear_increase_in_range(150, 0.01, 200, 0.04, t_resistance);

    if (t_resistance < 300)
        return get_linear_increase_in_range(200, 0.04, 300, 0.25, t_resistance);

    return 0.25;
}

double Mechanics::get_linear_increase_in_range(
    const unsigned x_min, const double y_min, const unsigned x_max, const double y_max, const unsigned x_curr) {
    check((x_curr >= x_min), "x_curr < x_min");
    check((x_curr <= x_max), "x_curr > x_max");

    int x_delta = static_cast<int>(x_max) - static_cast<int>(x_min);

    double y_delta = y_max - y_min;
    double k = y_delta / x_delta;

    return (x_curr - x_min) * k + y_min;
}

double Mechanics::get_partial_75_chance(const unsigned t_resistance) {
    // Piecewise-linear function that implements the following resistance table:
    //
    // Target resistance |  0-20 | 20-50 | 50-80 | 80-100 | 100-120 | 120-150 | 150-200 | 200-300 |
    // % Occurance       | 0-1 % | 1-2 % | 2-3 % | 3-4 %  |  4-6 %  |  6-11 % | 11-23 % |  23-55% |
    //
    // This formula only serves as an initial approximation and is likely incorrect.
    if (t_resistance < 20)
        return get_linear_increase_in_range(0, 0.0, 20, 0.01, t_resistance);

    if (t_resistance < 50)
        return get_linear_increase_in_range(20, 0.01, 50, 0.02, t_resistance);

    if (t_resistance < 80)
        return get_linear_increase_in_range(50, 0.02, 80, 0.03, t_resistance);

    if (t_resistance < 100)
        return get_linear_increase_in_range(80, 0.03, 100, 0.04, t_resistance);

    if (t_resistance < 120)
        return get_linear_increase_in_range(100, 0.04, 120, 0.06, t_resistance);

    if (t_resistance < 150)
        return get_linear_increase_in_range(120, 0.06, 150, 0.11, t_resistance);

    if (t_resistance < 200)
        return get_linear_increase_in_range(150, 0.11, 200, 0.23, t_resistance);

    if (t_resistance < 300)
        return get_linear_increase_in_range(200, 0.23, 300, 0.55, t_resistance);

    return 0.55;
}

double Mechanics::get_partial_50_chance(const unsigned t_resistance) {
    // Piecewise-linear function that implements the following resistance table:
    //
    // Target resistance |  0-10 | 10-20 | 20-30 | 30-40 | 40-50 | 50-60 |  60-70  | 70-80  |
    // % Occurance       | 0-2 % | 2-4 % | 4-5 % | 5-7 % | 7-9%  | 9-11 % | 11-13% | 13-15% |
    // cont.
    // Target resistance | 80-90  | 90-100  | 100-120 | 120-150 | 150-200 | 200-300 |
    // % Occurance       | 15-17% | 17-19%  | 19-24 % | 24-37 % | 37-48 % | 48-16 % |
    //
    // This formula only serves as an initial approximation and is likely incorrect.
    if (t_resistance < 10)
        return get_linear_increase_in_range(0, 0.0, 10, 0.02, t_resistance);

    if (t_resistance < 20)
        return get_linear_increase_in_range(10, 0.02, 20, 0.04, t_resistance);

    if (t_resistance < 30)
        return get_linear_increase_in_range(20, 0.04, 30, 0.05, t_resistance);

    if (t_resistance < 40)
        return get_linear_increase_in_range(30, 0.05, 40, 0.07, t_resistance);

    if (t_resistance < 50)
        return get_linear_increase_in_range(40, 0.07, 50, 0.09, t_resistance);

    if (t_resistance < 60)
        return get_linear_increase_in_range(50, 0.09, 60, 0.11, t_resistance);

    if (t_resistance < 70)
        return get_linear_increase_in_range(60, 0.11, 70, 0.13, t_resistance);

    if (t_resistance < 80)
        return get_linear_increase_in_range(70, 0.13, 80, 0.15, t_resistance);

    if (t_resistance < 90)
        return get_linear_increase_in_range(80, 0.15, 90, 0.17, t_resistance);

    if (t_resistance < 100)
        return get_linear_increase_in_range(90, 0.17, 100, 0.19, t_resistance);

    if (t_resistance < 120)
        return get_linear_increase_in_range(100, 0.19, 120, 0.24, t_resistance);

    if (t_resistance < 150)
        return get_linear_increase_in_range(120, 0.24, 150, 0.37, t_resistance);

    if (t_resistance < 200)
        return get_linear_increase_in_range(150, 0.37, 200, 0.48, t_resistance);

    if (t_resistance < 300)
        return get_linear_increase_in_range(200, 0.48, 300, 0.16, t_resistance);

    return 0.16;
}

double Mechanics::get_partial_25_chance(const unsigned t_resistance) {
    // Piecewise-linear function that implements the following resistance table:
    //
    // Target resistance |  0-10 | 10-20  | 20-30   | 30-40   | 40-50  | 50-60   |  60-70 | 70-80  |
    // % Occurance       | 0-6 % | 6-12 % | 12-18 % | 18-23 % | 23-28% | 28-33 % | 33-37% | 37-41% |
    // cont.
    // Target resistance | 80-90  | 90-100  | 100-120 | 120-150 | 150-200 | 200-300 |
    // % Occurance       | 41-45% | 45-47%  | 47-49 % | 49-39 % | 39-21 % | 21-3 %  |
    //
    // This formula only serves as an initial approximation and is likely incorrect.
    if (t_resistance < 10)
        return get_linear_increase_in_range(0, 0.0, 10, 0.06, t_resistance);

    if (t_resistance < 20)
        return get_linear_increase_in_range(10, 0.06, 20, 0.12, t_resistance);

    if (t_resistance < 30)
        return get_linear_increase_in_range(20, 0.12, 30, 0.18, t_resistance);

    if (t_resistance < 40)
        return get_linear_increase_in_range(30, 0.18, 40, 0.23, t_resistance);

    if (t_resistance < 50)
        return get_linear_increase_in_range(40, 0.23, 50, 0.28, t_resistance);

    if (t_resistance < 60)
        return get_linear_increase_in_range(50, 0.28, 60, 0.33, t_resistance);

    if (t_resistance < 70)
        return get_linear_increase_in_range(60, 0.33, 70, 0.37, t_resistance);

    if (t_resistance < 80)
        return get_linear_increase_in_range(70, 0.37, 80, 0.41, t_resistance);

    if (t_resistance < 90)
        return get_linear_increase_in_range(80, 0.41, 90, 0.45, t_resistance);

    if (t_resistance < 100)
        return get_linear_increase_in_range(90, 0.45, 100, 0.47, t_resistance);

    if (t_resistance < 120)
        return get_linear_increase_in_range(100, 0.47, 120, 0.49, t_resistance);

    if (t_resistance < 150)
        return get_linear_increase_in_range(120, 0.49, 150, 0.39, t_resistance);

    if (t_resistance < 200)
        return get_linear_increase_in_range(150, 0.39, 200, 0.21, t_resistance);

    if (t_resistance < 300)
        return get_linear_increase_in_range(200, 0.21, 300, 0.03, t_resistance);

    return 0.3;
}
