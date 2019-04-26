#include "StatisticsRotationExecutor.h"

#include "Spell.h"

bool description(ExecutorOutcome* lhs, ExecutorOutcome* rhs) {
    return StatisticsRotationExecutor::get_description_for_status(lhs->spell_status) >
            StatisticsRotationExecutor::get_description_for_status(rhs->spell_status);
}

bool value(ExecutorOutcome* lhs, ExecutorOutcome* rhs) {
    return lhs->value > rhs->value;
}

ExecutorOutcome::ExecutorOutcome(const QString &name,
                                 ExecutorResult result,
                                 unsigned value,
                                 SpellStatus spell_status) :
    name(name),
    result(result),
    value(value),
    spell_status(spell_status)
{}

StatisticsRotationExecutor::StatisticsRotationExecutor(const QString& executor_name) :
    executor_name(executor_name)
{}

QString StatisticsRotationExecutor::get_name() const {
    return this->executor_name;
}

unsigned StatisticsRotationExecutor::get_successful_casts() const {
    return this->successful_casts;
}

void StatisticsRotationExecutor::add_successful_casts(unsigned successful_casts) {
    this->successful_casts += successful_casts;
}

void StatisticsRotationExecutor::add_no_condition_group_fulfilled(unsigned no_condition_group_fulfilled) {
    this->no_condition_group_fulfilled += no_condition_group_fulfilled;
}

void StatisticsRotationExecutor::add_spell_status_map(const QMap<SpellStatus, unsigned>& spell_status_map) {
    QMap<SpellStatus, unsigned>::const_iterator it = spell_status_map.constBegin();
    while (it != spell_status_map.constEnd()) {
        if (!this->spell_status_map.contains(it.key()))
            this->spell_status_map[it.key()] = 0;

        this->spell_status_map[it.key()] += spell_status_map[it.key()];
        ++it;
    }
}

void StatisticsRotationExecutor::add(const StatisticsRotationExecutor* other) {
    add_successful_casts(other->successful_casts);
    add_no_condition_group_fulfilled(other->no_condition_group_fulfilled);
    add_spell_status_map(other->spell_status_map);
}

QString StatisticsRotationExecutor::get_description_for_status(const SpellStatus status) {
    switch (status) {
    case SpellStatus::Available:
        return "Available";
    case SpellStatus::BuffInactive:
        return "FAIL: Internal buff inactive";
    case SpellStatus::CastInProgress:
        return "FAIL: Cast in progress";
    case SpellStatus::InBattleStance:
        return "FAIL: In Battle Stance";
    case SpellStatus::InBerserkerStance:
        return "FAIL: In Berserker Stance";
    case SpellStatus::InDefensiveStance:
        return "FAIL: In Defensive Stance";
    case SpellStatus::IncorrectWeaponType:
        return "FAIL: Incorrect weapon type";
    case SpellStatus::InsufficientComboPoints:
        return "FAIL: Insufficient combo points";
    case SpellStatus::InsufficientResources:
        return "FAIL: Insufficient resources";
    case SpellStatus::NotEnabled:
        return "FAIL: Not enabled";
    case SpellStatus::NotInExecuteRange:
        return "FAIL: Not in execute range";
    case SpellStatus::OnCooldown:
        return "FAIL: On spell cooldown";
    case SpellStatus::OnGCD:
        return "FAIL: On global cooldown";
    case SpellStatus::OnStanceCooldown:
        return "FAIL: On stance cooldown";
    case SpellStatus::OnTrinketCooldown:
        return "FAIL: On shared trinket cooldown";
    case SpellStatus::OvercapResource:
        return "FAIL: Cast would exceed resource cap";
    case SpellStatus::DependentBuffInactive:
        return "FAIL: Depends on inactive buff";
    }

    return "<missing description for SpellStatus>";
}

QString StatisticsRotationExecutor::get_description_for_executor_result(const ExecutorResult result) {
    switch (result) {
    case ExecutorResult::Success:
        return "Success";
    case ExecutorResult::SpellStatusFail:
        return "SpellStatus";
    case ExecutorResult::ConditionGroupFail:
        return "ConditionGroup";
    }

    return "<missing description for ExecutorResult>";
}

QList<ExecutorOutcome*> StatisticsRotationExecutor::get_list_of_executor_outcomes() const {
    QList<ExecutorOutcome*> outcome_list;

    outcome_list = {
        new ExecutorOutcome(executor_name, ExecutorResult::Success, successful_casts, SpellStatus::Available),
        new ExecutorOutcome(executor_name, ExecutorResult::ConditionGroupFail, no_condition_group_fulfilled, SpellStatus::Available),
    };

    QMap<SpellStatus, unsigned>::const_iterator it = spell_status_map.constBegin();
    while (it != spell_status_map.constEnd()) {
        if (it.value() == 0) {
            ++it;
            continue;
        }

        outcome_list.append(new ExecutorOutcome(executor_name, ExecutorResult::SpellStatusFail, it.value(), it.key()));
        ++it;
    }

    return outcome_list;
}
