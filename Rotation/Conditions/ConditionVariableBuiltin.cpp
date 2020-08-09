#include "ConditionVariableBuiltin.h"

#include <cmath>

#include "AutoShot.h"
#include "Character.h"
#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "Druid.h"
#include "Engine.h"
#include "MainhandAttack.h"
#include "Rogue.h"
#include "SimSettings.h"
#include "Utils/Check.h"
#include "Utils/CompareDouble.h"

ConditionVariableBuiltin::ConditionVariableBuiltin(Character* pchar,
                                                   const BuiltinVariables builtin,
                                                   const Comparator comparator,
                                                   const double cmp_value) :
    Condition(comparator), pchar(pchar), engine(pchar->get_engine()), builtin(builtin), rhs_value(cmp_value) {}

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
        auto mh_attack = pchar->get_spells()->get_mh_attack();
        double delta = pchar->get_engine()->get_current_priority() - std::max(mh_attack->get_last_used(), 0.0);
        return cmp_values(delta);
    }
    case BuiltinVariables::AutoShotTimer: {
        auto auto_shot = pchar->get_spells()->get_auto_shot();
        double delta = pchar->get_engine()->get_current_priority() - std::max(auto_shot->get_last_used(), 0.0);
        return cmp_values(delta);
    }
    case BuiltinVariables::MeleeAP:
        return cmp_values(pchar->get_stats()->get_melee_ap());
    case BuiltinVariables::ComboPoints: {
        const auto rogue = dynamic_cast<Rogue*>(pchar);
        if (rogue != nullptr)
            return cmp_values(rogue->get_combo_points());

        const auto druid = dynamic_cast<Druid*>(pchar);
        if (druid != nullptr)
            return cmp_values(druid->get_combo_points());

        return false;
    }
    case BuiltinVariables::TimeRemainingGCD:
        return cmp_values(pchar->time_until_action_ready());

    default:
        check(false, "ConditionVariableBuiltin::condition_fulfilled reached end of switch");
        return false;
    }
}

QString ConditionVariableBuiltin::condition_description() const {
    if (builtin == BuiltinVariables::TargetHealth)
        return QString("Target Health %1 %2%").arg(comparator_as_string()).arg(QString::number(rhs_value, 'f', 1));
    if (builtin == BuiltinVariables::TimeRemainingEncounter)
        return QString("Time Remaining Encounter %1 %2 seconds").arg(comparator_as_string()).arg(QString::number(rhs_value, 'f', 1));
    if (builtin == BuiltinVariables::TimeRemainingExecute)
        return QString("Time Remaining Until Execute %1 %2 seconds").arg(comparator_as_string()).arg(QString::number(rhs_value, 'f', 1));
    if (builtin == BuiltinVariables::SwingTimer)
        return QString("Time Since Mainhand Swing %1 %2 seconds").arg(comparator_as_string()).arg(QString::number(rhs_value, 'f', 1));
    if (builtin == BuiltinVariables::AutoShotTimer)
        return QString("Time Since Auto Shot %1 %2 seconds").arg(comparator_as_string()).arg(QString::number(rhs_value, 'f', 1));
    if (builtin == BuiltinVariables::MeleeAP)
        return QString("Melee Attack Power %1 %2").arg(comparator_as_string()).arg(QString::number(rhs_value, 'f', 0));
    if (builtin == BuiltinVariables::ComboPoints)
        return QString("Combo Points %1 %2").arg(comparator_as_string()).arg(QString::number(rhs_value, 'f', 0));
    if (builtin == BuiltinVariables::TimeRemainingGCD)
        return QString("Time Remaining GCD %1 %2 seconds").arg(comparator_as_string()).arg(QString::number(rhs_value, 'f', 1));

    return "<builtin variable is missing condition description>";
}

bool ConditionVariableBuiltin::cmp_values(const double lhs_value) const {
    switch (comparator) {
    case Comparator::Less:
        return lhs_value < rhs_value;
    case Comparator::Leq:
        return almost_equal(lhs_value, rhs_value) || lhs_value < rhs_value;
    case Comparator::Eq:
        return almost_equal(lhs_value, rhs_value);
    case Comparator::Geq:
        return almost_equal(lhs_value, rhs_value) || lhs_value > rhs_value;
    case Comparator::Greater:
        return lhs_value > rhs_value;
    default:
        check(false, "ConditionVariableBuiltin::cmp_values reached end of switch");
        return false;
    }
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
    if (var_name == "time_remaining_gcd")
        return BuiltinVariables::TimeRemainingGCD;

    return BuiltinVariables::Undefined;
}
