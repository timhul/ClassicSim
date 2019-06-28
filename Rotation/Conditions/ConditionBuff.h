#pragma once

#include "Condition.h"

class Buff;

class ConditionBuff : public Condition {
public:
    ConditionBuff(Buff *buff, const int comparator, const double cmp_value);

    bool condition_fulfilled() const override;
    QString condition_description() const override;

    Buff* buff;
    const double cmp_value;
};
