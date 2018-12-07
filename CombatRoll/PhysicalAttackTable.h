#ifndef PHYSICALATTACKTABLE_H
#define PHYSICALATTACKTABLE_H

#include <math.h>
#include "PhysicalAttackResult.h"

class PhysicalAttackTable {
public:
    virtual ~PhysicalAttackTable() = default;

    virtual int get_outcome(const unsigned roll,
                            const double crit_mod,
                            const bool include_dodge,
                            const bool include_parry,
                            const bool include_block,
                            const bool include_miss) = 0;
    virtual void dump_table(void) = 0;
    virtual void update_miss_chance(const double hit) = 0;
};

#endif // PHYSICALATTACKTABLE_H
