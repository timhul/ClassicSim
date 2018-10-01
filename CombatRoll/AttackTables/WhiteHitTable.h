#ifndef WHITEHITTABLE_H
#define WHITEHITTABLE_H

#include "AttackTable.h"

class Random;

class WhiteHitTable: public AttackTable {
public:
    WhiteHitTable(Random* random, const int wpn_skill, const double miss, const double dodge, const double parry,
                  const double glancing, const double block,  const double critical);

    int get_outcome(const unsigned roll,
                    const double crit_mod,
                    const bool include_dodge = true,
                    const bool include_parry = true,
                    const bool include_block = true,
                    const bool include_miss = true) override;
    void dump_table(void) override;
    void update_crit_chance(const double critical) override;
    void update_miss_chance(const double miss) override;
    void update_dodge_chance(const double dodge);
    void update_parry_chance(const double parry);
    void update_glancing_chance(const double glancing);
    void update_block_chance(const double block);

    int get_wpn_skill();

    void update_ranges();

protected:
private:
    Random* random;
    const int wpn_skill;

    double miss;
    double dodge;
    double parry;
    double glancing;
    double block;
    double critical;

    unsigned range{};
    unsigned miss_range{};
    unsigned dodge_range{};
    unsigned parry_range{};
    unsigned glancing_range{};
    unsigned block_range{};
    unsigned critical_range{};
};

#endif // WHITEHITTABLE_H
