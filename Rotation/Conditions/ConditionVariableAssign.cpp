
#include "ConditionVariableAssign.h"
#include "VariableAssign.h"

ConditionVariableAssign::ConditionVariableAssign(VariableAssign* variable,
                                                 const int comparator,
                                                 const bool cmp_value) :
    variable(variable),
    comparator(comparator),
    cmp_value(cmp_value)
{}

bool ConditionVariableAssign::condition_fulfilled() const {
    return cmp_value == variable->get_variable_value();
}
