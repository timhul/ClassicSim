#ifndef CONDITIONBUILTIN_H
#define CONDITIONBUILTIN_H

#include "Condition.h"

namespace BuiltinVariables {
    static const int TargetHealth = 0;
    static const int TimeRemainingEncounter = 1;
    static const int TimeRemainingExecute = 2;
}


class ConditionVariableBuiltin : public Condition {
public:
    ConditionVariableBuiltin(const int builtin, const int comparator, const float cmp_value);


    bool condition_fulfilled() const override;

private:
    const int builtin;
    const int comparator;
    const float cmp_value;

    bool cmp_mh_swing() const;
};

#endif // CONDITIONBUILTIN_H
