#ifndef WHITEHITTABLE_H
#define WHITEHITTABLE_H

#include "AttackTable.h"

class WhiteHitTable: public AttackTable {
public:
    WhiteHitTable(const int wpn_skill, const float miss, const float dodge, const float parry,
                  const float glancing, const float block,  const float critical);

    int get_outcome(const int, const float crit_mod) override;
    void dump_table(void) override;
    void update_crit_chance(const float critical) override;
    void update_miss_chance(const float miss) override;
    void update_dodge_chance(const float dodge);
    void update_parry_chance(const float parry);
    void update_glancing_chance(const float glancing);
    void update_block_chance(const float block);

    int get_wpn_skill();

    void update_ranges();

protected:
private:
    const int wpn_skill;

    float miss;
    float dodge;
    float parry;
    float glancing;
    float block;
    float critical;

    int range;
    int miss_range;
    int dodge_range;
    int parry_range;
    int glancing_range;
    int block_range;
    int critical_range;
};

#endif // WHITEHITTABLE_H
