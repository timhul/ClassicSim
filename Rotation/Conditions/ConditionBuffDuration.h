#pragma once

#include "Condition.h"

class Buff;

class ConditionBuffDuration : public Condition {
public:
    ConditionBuffDuration(Buff *buff, const Comparator comparator, const double cmp_value);

    bool condition_fulfilled() const override;
    QString condition_description() const override;

    Buff* buff;
    const double cmp_value;
};
