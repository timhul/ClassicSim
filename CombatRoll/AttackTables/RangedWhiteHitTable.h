#ifndef RANGEDWHITEHITTABLE_H
#define RANGEDWHITEHITTABLE_H

#include "PhysicalAttackResult.h"

class Random;

class RangedWhiteHitTable {
public:
    RangedWhiteHitTable(Random* random,
                        const int wpn_skill,
                        const unsigned miss,
                        const double block);

    int get_outcome(const unsigned roll,
                    const unsigned crit_chance,
                    const bool include_block = true,
                    const bool include_miss = true);

    void update_miss_chance(const unsigned miss);
    void update_block_chance(const double block);

    int get_wpn_skill() const;

    void update_ranges();

private:
    Random* random;
    const int wpn_skill;

    unsigned miss_range;
    unsigned block_range;
};

#endif // RANGEDWHITEHITTABLE_H
