
#include "Mechanics.h"
#include "Target.h"

Mechanics::Mechanics(Target* target):
    target(target)
{}

double Mechanics::get_yellow_miss_chance(const int wpn_skill) const {
    return get_2h_white_miss_chance(wpn_skill);
}

double Mechanics::get_dw_white_miss_chance(const int wpn_skill) const {
    // Note that it assumes defense diff is positive.
    // Formula currently not correct when diff is negative (player wpn skill > target defense)
    int defense_diff = target->get_defense() - wpn_skill;

    if (defense_diff > 10)
        return std::max(0.0, 0.26 + (defense_diff - 10) * 0.004);
    return std::max(0.0, 0.24 + defense_diff * 0.001);
}

double Mechanics::get_2h_white_miss_chance(const int wpn_skill) const {
    // Note that it assumes defense diff is positive.
    // Formula currently not correct when diff is negative (player wpn skill > target defense)
    int defense_diff = target->get_defense() - wpn_skill;

    if (defense_diff > 10)
        return std::max(0.0, 0.07 + (defense_diff - 10) * 0.004);
    return std::max(0.0, 0.05 + defense_diff * 0.001);
}

double Mechanics::get_1h_white_miss_chance(const int wpn_skill) const {
    // Note that this is not for dual-wield, this is when only a single 1hander is equipped.
    return get_2h_white_miss_chance(wpn_skill);
}

double Mechanics::get_glancing_blow_chance(const int clvl) const {
    // TODO: Non-melee classes do not follow this formula.
    int level_diff = target->get_lvl() - clvl;
    if (level_diff < 0)
        return 0.0;

    return 0.1 + level_diff * 5 * 0.02;
}

double Mechanics::get_dodge_chance(const int wpn_skill) const {
    int defense_diff = wpn_skill - target->get_defense();

    if (defense_diff > 0)
        return 0.05 - defense_diff * 0.0004;
    return 0.05;
}

double Mechanics::get_parry_chance(const int) const {
    // TODO: Add possibility to activate parry chance and have it affected by wpn skill.
    return 0.0;
}

double Mechanics::get_block_chance() const {
    // TODO: Add possibility to activate block chance and have it affected by wpn skill.
    return 0.0;
}

int Mechanics::get_boss_base_armor() const {
    return 4960;
}

double Mechanics::get_reduction_from_armor(const int armor, const int clvl) const {
    return armor / (armor + 400 + 85 * (clvl + 4.5 * (clvl - 60)));
}

double Mechanics::get_glancing_blow_dmg_penalty(const int wpn_skill) const {
    return std::max(0.7, std::min(1.0, 1.0 - (target->get_defense() - wpn_skill - 5) * 0.03));
}
