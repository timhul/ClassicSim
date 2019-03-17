#ifndef RANGEDWHITEHITTABLE_H
#define RANGEDWHITEHITTABLE_H

#include "PhysicalAttackResult.h"

class Random;

class RangedWhiteHitTable {
public:
    RangedWhiteHitTable(Random* random,
                        const int wpn_skill,
                        const double miss,
                        const double dodge,
                        const double block);

    int get_outcome(const unsigned roll,
                    const double crit_chance,
                    const bool include_dodge = true,
                    const bool include_block = true,
                    const bool include_miss = true);

    void update_miss_chance(const double miss);
    void update_dodge_chance(const double dodge);
    void update_block_chance(const double block);

    int get_wpn_skill();

    void update_ranges();

private:
    Random* random;
    const int wpn_skill;

    double miss;
    double dodge;
    double block;
    double critical;

    unsigned range{};
    unsigned miss_range{};
    unsigned dodge_range{};
    unsigned block_range{};
};

#endif // RANGEDWHITEHITTABLE_H
