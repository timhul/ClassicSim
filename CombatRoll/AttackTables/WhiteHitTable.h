#ifndef WHITEHITTABLE_H
#define WHITEHITTABLE_H

#include "AttackTable.h"

class WhiteHitTable: public AttackTable {
public:
    WhiteHitTable(const float miss, const float dodge, const float parry,
                  const float glancing, const float block,  const float critical);

    int get_outcome(const int, const float crit_mod) override;
    void dump_table(void) override;
    void update_crit_chance(const float critical) override;

    void set_miss_range(const int range);
    void set_dodge_range(const int range);
    void set_parry_range(const int range);
    void set_block_range(const int range);
    void set_glancing_range(const int range);

protected:
private:
    float miss;
    float dodge;
    float parry;
    float glancing;
    float block;
    float critical;
    int wpn_skill;

    int range;
    int miss_range;
    int dodge_range;
    int parry_range;
    int glancing_range;
    int block_range;
    int critical_range;
};

#endif // WHITEHITTABLE_H
