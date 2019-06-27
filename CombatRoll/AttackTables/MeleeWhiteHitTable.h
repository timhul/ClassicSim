#pragma once

#include "PhysicalAttackResult.h"

class Random;

class MeleeWhiteHitTable {
public:
    MeleeWhiteHitTable(Random* random,
                  const unsigned wpn_skill,
                  const unsigned miss_range,
                  const double dodge,
                  const double parry,
                  const double glancing,
                  const double block);

    int get_outcome(const unsigned roll,
                    const unsigned crit_chance,
                    const bool include_dodge = true,
                    const bool include_parry = true,
                    const bool include_block = true,
                    const bool include_miss = true);

    void update_miss_chance(const unsigned miss_range);
    void update_dodge_chance(const double dodge);
    void update_parry_chance(const double parry);
    void update_glancing_chance(const double glancing);
    void update_block_chance(const double block);

    const unsigned wpn_skill;

private:
    Random* random;

    unsigned miss_range;
    unsigned dodge_range;
    unsigned parry_range;
    unsigned glancing_range;
    unsigned block_range;
};
