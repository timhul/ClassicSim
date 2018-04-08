#ifndef MELEESPECIALTABLE_H
#define MELEESPECIALTABLE_H

#include "AttackTable.h"
#include "Random.h"

class MeleeSpecialTable: public AttackTable {
public:
    MeleeSpecialTable(Random* _rand,
                      const float miss, const float dodge, const float parry,
                      const float block, const float critical);

    int get_outcome(const int) override;
    void dump_table(void) override;
    void update_crit_chance(const float critical) override;

protected:
private:
    Random* random;

    int miss_range;
    int dodge_range;
    int parry_range;
    int block_range;
    int critical_range;
};

#endif // MELEESPECIALTABLE_H
