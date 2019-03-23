#include "ConditionVariableBuiltin.h"

#include <cmath>

#include "AutoShot.h"
#include "Character.h"
#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "Engine.h"
#include "MainhandAttack.h"
#include "Rogue.h"
#include "SimSettings.h"
#include "Utils/Check.h"

ConditionVariableBuiltin::ConditionVariableBuiltin(Character* pchar,
                                                   const BuiltinVariables builtin,
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
        int combat_length = pchar->get_sim_settings()->get_combat_length();
        double remaining_health = (combat_length - engine->get_current_priority()) / combat_length;
        return cmp_values(remaining_health);
    }
    case BuiltinVariables::TimeRemainingEncounter: {
        int combat_length = pchar->get_sim_settings()->get_combat_length();
        double remaining_encounter_time = combat_length - engine->get_current_priority();
        return cmp_values(remaining_encounter_time);
    }
    case BuiltinVariables::TimeRemainingExecute: {
        int combat_length = pchar->get_sim_settings()->get_combat_length();
        double execute_threshold = pchar->get_sim_settings()->get_execute_threshold();
        double remaining_execute_time = combat_length * (1 - execute_threshold) - engine->get_current_priority();
        return cmp_values(remaining_execute_time);
    }
    case BuiltinVariables::SwingTimer: {
        auto* mh_attack =  pchar->get_spells()->get_mh_attack();
        double delta = pchar->get_engine()->get_current_priority() - std::max(mh_attack->get_last_used(), 0.0);
        return cmp_values(delta);
    }
    case BuiltinVariables::AutoShotTimer: {
        auto* auto_shot = pchar->get_spells()->get_auto_shot();
        double delta = pchar->get_engine()->get_current_priority() - std::max(auto_shot->get_last_used(), 0.0);
        return cmp_values(delta);
    }
    case BuiltinVariables::MeleeAP:
        return cmp_values(pchar->get_stats()->get_melee_ap());
    case BuiltinVariables::ComboPoints:
        return cmp_values(dynamic_cast<Rogue*>(pchar)->get_combo_points());
    default:
        check(false, "Reached end of switch");
        return false;
    }
}

bool ConditionVariableBuiltin::cmp_values(const double lhs_value) const {
    switch (comparator) {
    case Comparators::less:
        return lhs_value < rhs_value;
    case Comparators::leq:
        return almost_equal(lhs_value, rhs_value) || lhs_value < rhs_value;
    case Comparators::eq:
        return almost_equal(lhs_value, rhs_value);
    case Comparators::geq:
        return almost_equal(lhs_value, rhs_value) || lhs_value > rhs_value;
    case Comparators::greater:
        return lhs_value > rhs_value;
    default:
        check(false, "Reached end of switch");
        return false;
    }
}

double ConditionVariableBuiltin::delta(double lhs, double rhs) {
    return (lhs - rhs) < 0 ?  (lhs - rhs) * - 1 : (lhs - rhs);
}

bool ConditionVariableBuiltin::almost_equal(double lhs, double rhs) {
    return delta(lhs, rhs) < 0.000001;
}

BuiltinVariables ConditionVariableBuiltin::get_builtin_variable(const QString& var_name) {
    if (var_name == "target_health")
        return BuiltinVariables::TargetHealth;
    if (var_name == "time_remaining_encounter")
        return BuiltinVariables::TimeRemainingEncounter;
    if (var_name == "time_remaining_execute")
        return BuiltinVariables::TimeRemainingExecute;
    if (var_name == "time_since_swing")
        return BuiltinVariables::SwingTimer;
    if (var_name == "time_since_auto_shot")
        return BuiltinVariables::AutoShotTimer;
    if (var_name == "melee_ap")
        return BuiltinVariables::MeleeAP;
    if (var_name == "combo_points")
        return BuiltinVariables::ComboPoints;

    return BuiltinVariables::Undefined;
}
