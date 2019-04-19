
#include "ConditionVariableAssign.h"
#include "VariableAssign.h"

ConditionVariableAssign::ConditionVariableAssign(VariableAssign* variable,
                                                 const int comparator,
                                                 const bool cmp_value) :
    Condition(comparator),
    variable(variable),
    cmp_value(cmp_value)
{}

bool ConditionVariableAssign::condition_fulfilled() const {
    return cmp_value == variable->get_variable_value();
}

QString ConditionVariableAssign::condition_description() const {
    return "Condition description for VariableAssign not implemented";
}
