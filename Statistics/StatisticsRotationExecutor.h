#pragma once

#include <QMap>

class StatisticsRotationExecutor;
enum class SpellStatus: int;

enum class ExecutorResult: int {
    SpellStatusFail,
    ConditionGroupFail,
    Success,
};

class ExecutorOutcome {
public:
    ExecutorOutcome(const QString& name,
                    ExecutorResult result,
                    unsigned value,
                    SpellStatus spell_status);

    const QString name;
    const ExecutorResult result;
    const unsigned value;
    const SpellStatus spell_status;
};

bool description(ExecutorOutcome* lhs, ExecutorOutcome* rhs);
bool value(ExecutorOutcome* lhs, ExecutorOutcome* rhs);

class StatisticsRotationExecutor {
public:
    StatisticsRotationExecutor(const QString& executor_name);

    QString get_name() const;
    void add_successful_casts(unsigned successful_casts);
    void add_no_condition_group_fulfilled(unsigned no_condition_group_fulfilled);
    void add_spell_status_map(const QMap<SpellStatus, unsigned>& spell_status_map);
    void add(const StatisticsRotationExecutor*);

    static QString get_description_for_status(const SpellStatus status);
    static QString get_description_for_executor_result(const ExecutorResult result);
    QList<ExecutorOutcome*> get_list_of_executor_outcomes() const;

private:
    const QString executor_name;
    unsigned successful_casts {0};
    unsigned no_condition_group_fulfilled {0};
    QMap<SpellStatus, unsigned> spell_status_map;
};
