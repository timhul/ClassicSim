
#include "ConditionVariableBuiltin.h"


ConditionVariableBuiltin::ConditionVariableBuiltin(const int builtin,
                                                   const int comparator,
                                                   const float cmp_value) :
    builtin(builtin),
    comparator(comparator),
    cmp_value(cmp_value)
{}

bool ConditionVariableBuiltin::condition_fulfilled() const {
    switch (builtin) {
    case BuiltinVariables::TargetHealth:
        // TODO: implement
        return false;
    case BuiltinVariables::TimeRemainingEncounter:
        // TODO: implement
        return false;
    case BuiltinVariables::TimeRemainingExecute:
        // TODO: implement
        return false;
    }

    assert(false);
    return false;
}
