#pragma once

#include "Condition.h"

class Character;
class Engine;

enum BuiltinVariables
{
    Undefined = -1,
    TargetHealth,
    TimeRemainingEncounter,
    TimeRemainingExecute,
    SwingTimer,
    AutoShotTimer,
    MeleeAP,
    ComboPoints
};

class ConditionVariableBuiltin : public Condition {
public:
    ConditionVariableBuiltin(Character* pchar, const BuiltinVariables builtin, const Comparator comparator, const double rhs_value);

    bool condition_fulfilled() const override;
    QString condition_description() const override;

    static BuiltinVariables get_builtin_variable(const QString& var_name);

    Character* pchar;
    Engine* engine;
    const BuiltinVariables builtin;
    const double rhs_value;

    bool cmp_values(const double lhs_value) const;
};
