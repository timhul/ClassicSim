
#include "Mechanics.h"

float Mechanics::get_yellow_miss_chance(const int wpn_skill) const {
    return get_2h_white_miss_chance(wpn_skill);
}

float Mechanics::get_dw_white_miss_chance(const int wpn_skill) const {
    // Note that it assumes defense diff is positive.
    // Formula currently not correct when diff is negative (player wpn skill > target defense)
    int defense_diff = tdefense - wpn_skill;

    if (defense_diff > 10)
        return std::max(0.0, 0.26 - hit_chance + (defense_diff - 10) * 0.004);
    return std::max(0.0, 0.24 - hit_chance + defense_diff * 0.001);
}

float Mechanics::get_2h_white_miss_chance(const int wpn_skill) const {
    // Note that it assumes defense diff is positive.
    // Formula currently not correct when diff is negative (player wpn skill > target defense)
    int defense_diff = tdefense - wpn_skill;

    if (defense_diff > 10)
        return std::max(0.0, 0.07 - hit_chance + (defense_diff - 10) * 0.004);
    return std::max(0.0, 0.05 - hit_chance + defense_diff * 0.001);
}

float Mechanics::get_1h_white_miss_chance(const int wpn_skill) const {
    // Note that this is not for dual-wield, this is when only a single 1hander is equipped.
    return get_2h_white_miss_chance(wpn_skill);
}

float Mechanics::get_glancing_blow_chance(const int clvl) const {
    // TODO: Non-melee classes do not follow this formula.
    int level_diff = tlvl - clvl;
    if (level_diff < 0)
        return 0.0;

    return 0.1 + level_diff * 5 * 0.02;
}

float Mechanics::get_dodge_chance(const int wpn_skill) const {
    int defense_diff = wpn_skill - tdefense;

    if (defense_diff > 0)
        return 0.05 - defense_diff * 0.0004;
    return 0.05;
}

float Mechanics::get_parry_chance(const int) const {
    // TODO: Add possibility to activate parry chance and have it affected by wpn skill.
    return 0.0;
}

float Mechanics::get_block_chance(void) const {
    // TODO: Add possibility to activate block chance and have it affected by wpn skill.
    return 0.0;
}

void Mechanics::set_tlvl(const int tlvl) {
    this->tlvl = tlvl;
    this->tdefense = tlvl * 5;
}

float Mechanics::get_glancing_blow_dmg_penalty(const int clvl, const int wpn_skill) const {
    int level_diff = tlvl - clvl;
    if (level_diff < 0)
        return 1.0;

    return std::max(0.7, std::min(1.0, 1.0 - (tdefense - wpn_skill - 5) * 0.03));
}
