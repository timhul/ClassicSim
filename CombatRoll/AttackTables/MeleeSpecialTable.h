#ifndef MELEESPECIALTABLE_H
#define MELEESPECIALTABLE_H

#include "AttackTable.h"
#include "AttackResult.h"
#include "Random.h"

class MeleeSpecialTable: public AttackTable {
public:
    MeleeSpecialTable(Random* _rand, const int wpn_skill,
                      const float miss, const float dodge, const float parry,
                      const float block, const float critical);

    int get_outcome(const int, const float crit_mod) override;
    void dump_table(void) override;
    void update_crit_chance(const float critical) override;
    void update_miss_chance(const float miss) override;
    void update_dodge_chance(const float dodge);
    void update_parry_chance(const float parry);
    void update_block_chance(const float block);

    int get_wpn_skill();

    void update_ranges();

protected:
private:
    Random* random;
    const int wpn_skill;

    float miss;
    float dodge;
    float parry;
    float block;
    float critical;

    int miss_range;
    int dodge_range;
    int parry_range;
    int block_range;
    int critical_range;
};

#endif // MELEESPECIALTABLE_H
