#pragma once

#include <QString>

enum class Comparator: int {
    Less,
    Leq,
    Eq,
    Geq,
    Greater,
    False,
    True,
};

enum class CompareValueType: int {
    Boolean,
    Float,
};

enum class ConditionType: int {
    BuffDurationCondition,
    BuffStacksCondition,
    SpellCondition,
    ResourceCondition,
    VariableBuiltinCondition,
};

enum class LogicalConnective: bool {
    AND,
    OR,
};

enum class BuffCompareType: int {
    Duration,
    Charges,
};

class Sentence {
public:
    LogicalConnective logical_connective;
    ConditionType condition_type;
    QString type_value;
    Comparator mathematical_symbol;
    CompareValueType compared_value_type;
    QString compared_value;

    QString logical_connective_as_string() const;
    QString condition_type_as_string() const;
    QString mathematical_symbol_as_string() const;
    QString compared_value_type_as_string() const;

    void dump() const;
};

class Condition {
public:
    Condition(const Comparator comparator);
    virtual ~Condition() = default;

    virtual bool condition_fulfilled() const = 0;
    virtual QString condition_description() const = 0;

    const Comparator comparator;

protected:
    QString comparator_as_string() const;
};
