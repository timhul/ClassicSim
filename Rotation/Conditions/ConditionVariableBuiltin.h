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
    static const int SwingTimer = 3;
    static const int MeleeAP = 4;
    static const int ComboPoints = 5;
}


class ConditionVariableBuiltin : public Condition {
public:
    ConditionVariableBuiltin(Character*,
                             const int builtin,
                             const int comparator,
                             const double rhs_value);


    bool condition_fulfilled() const override;

private:
    Character* pchar;
    Engine* engine;
    const int builtin;
    const int comparator;
    const double rhs_value;

    bool cmp_values(const double lhs_value) const;

    static double delta(double lhs, double rhs);
    static bool almost_equal(double lhs, double rhs);
};

#endif // CONDITIONBUILTIN_H
