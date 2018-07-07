#ifndef CONDITIONBUILTIN_H
#define CONDITIONBUILTIN_H

#include "Condition.h"

class Character;
class Engine;

namespace BuiltinVariables {
    static const int Undefined = -1;
    static const int TargetHealth = 0;
    static const int TimeRemainingEncounter = 1;
    static const int TimeRemainingExecute = 2;
}


class ConditionVariableBuiltin : public Condition {
public:
    ConditionVariableBuiltin(Character*,
                             const int builtin,
                             const int comparator,
                             const float rhs_value);


    bool condition_fulfilled() const override;

private:
    Character* pchar;
    Engine* engine;
    const int builtin;
    const int comparator;
    const float rhs_value;

    bool cmp_values(const float lhs_value) const;
};

#endif // CONDITIONBUILTIN_H
