#ifndef ATTACKTABLE_H
#define ATTACKTABLE_H

#include <math.h>
#include "AttackResult.h"

class AttackTable {
public:
    virtual ~AttackTable() {}
    virtual int get_outcome(const int, const float) = 0;
    virtual void dump_table(void) = 0;
    virtual void update_crit_chance(const float critical) = 0;
    virtual void update_miss_chance(const float hit) = 0;
protected:
private:
};

#endif // ATTACKTABLE_H
