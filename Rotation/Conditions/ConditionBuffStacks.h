#pragma once

#include "Condition.h"

class Buff;

class ConditionBuffStacks : public Condition {
public:
    ConditionBuffStacks(Buff* buff, const Comparator comparator, const int cmp_value);

    bool condition_fulfilled() const override;
    QString condition_description() const override;

    Buff* buff;
    const int cmp_value;
};
