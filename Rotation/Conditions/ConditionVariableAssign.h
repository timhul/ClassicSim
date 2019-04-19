#ifndef CONDITIONVARIABLEBOOL_H
#define CONDITIONVARIABLEBOOL_H

#include "Condition.h"

class VariableAssign;

class ConditionVariableAssign : public Condition {
public:
    ConditionVariableAssign(VariableAssign* variable, const int comparator, const bool cmp_value);

    bool condition_fulfilled() const override;
    QString condition_description() const override;

private:
    const VariableAssign* variable;
    const bool cmp_value;
};

#endif // CONDITIONVARIABLEBOOL_H
