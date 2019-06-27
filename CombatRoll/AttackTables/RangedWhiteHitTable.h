#pragma once

#include "PhysicalAttackResult.h"

class Random;

class RangedWhiteHitTable {
public:
    RangedWhiteHitTable(Random* random,
                        const unsigned wpn_skill,
                        const unsigned miss,
                        const double block);

    int get_outcome(const unsigned roll,
                    const unsigned crit_chance,
                    const bool include_block = true,
                    const bool include_miss = true);

    void update_miss_chance(const unsigned miss);
    void update_block_chance(const double block);
    void update_ranges();

    const unsigned wpn_skill;

private:
    Random* random;

    unsigned miss_range;
    unsigned block_range;
};
