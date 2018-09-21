#ifndef CONDITIONBUFF_H
#define CONDITIONBUFF_H

#include "Condition.h"

class Buff;

class ConditionBuff : public Condition {
public:
    ConditionBuff(Buff *buff, const int comparator, const double cmp_value);

    bool condition_fulfilled() const override;

private:
    Buff* buff;
    const int comparator;
    const double cmp_value;
};

#endif // CONDITIONBUFF_H
