
#include "ConditionVariableBuiltin.h"
#include "Character.h"
#include "Engine.h"

ConditionVariableBuiltin::ConditionVariableBuiltin(Character* pchar,
                                                   const int builtin,
                                                   const int comparator,
                                                   const double cmp_value) :
    pchar(pchar),
    engine(pchar->get_engine()),
    builtin(builtin),
    comparator(comparator),
    rhs_value(cmp_value)
{}

bool ConditionVariableBuiltin::condition_fulfilled() const {
    switch (builtin) {
    case BuiltinVariables::TargetHealth: {
        // TODO: Remove knowledge of fight length
        double remaining_health = (300 - engine->get_current_priority()) / 300;
        return cmp_values(remaining_health);
    }
    case BuiltinVariables::TimeRemainingEncounter: {
        // TODO: Remove knowledge of fight length
        double remaining_encounter_time = 300 - engine->get_current_priority();
        return cmp_values(remaining_encounter_time);
    }
    case BuiltinVariables::TimeRemainingExecute: {
        // TODO: Refactor this check into separate target mechanic.
        double remaining_execute_time = 300 * 0.8 - engine->get_current_priority();
        return cmp_values(remaining_execute_time);
    }
    default:
        assert(false);
        return false;
    }
}

bool ConditionVariableBuiltin::cmp_values(const double lhs_value) const {
    switch (comparator) {
    case Comparators::less:
    case Comparators::leq:
        return lhs_value < rhs_value;
    case Comparators::eq:
        return (lhs_value - rhs_value) < 0.000001;
    case Comparators::geq:
    case Comparators::greater:
        return lhs_value > rhs_value;
    default:
        assert(false);
        return false;
    }
}
