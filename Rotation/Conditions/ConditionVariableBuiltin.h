#ifndef CONDITIONBUILTIN_H
#define CONDITIONBUILTIN_H

#include "Condition.h"

class Character;
class Engine;

enum BuiltinVariables {
    Undefined = -1,
    TargetHealth,
    TimeRemainingEncounter,
    TimeRemainingExecute,
    SwingTimer,
    MeleeAP,
    ComboPoints
};

class ConditionVariableBuiltin : public Condition {
public:
    ConditionVariableBuiltin(Character*,
                             const BuiltinVariables builtin,
                             const int comparator,
                             const double rhs_value);

    bool condition_fulfilled() const override;
    static BuiltinVariables get_builtin_variable(const QString& var_name);

private:
    Character* pchar;
    Engine* engine;
    const BuiltinVariables builtin;
    const int comparator;
    const double rhs_value;

    bool cmp_values(const double lhs_value) const;

    static double delta(double lhs, double rhs);
    static bool almost_equal(double lhs, double rhs);
};

#endif // CONDITIONBUILTIN_H
