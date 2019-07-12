#include "Condition.h"

#include <QDebug>

QString Sentence::logical_connective_as_string() const {
    switch (logical_connective) {
    case LogicalConnective::AND:
        return "AND";
    case LogicalConnective::OR:
        return "OR";
    }
}

QString Sentence::condition_type_as_string() const  {
    switch (condition_type) {
    case ConditionType::BuffDurationCondition:
        return "BUFF_DURATION";
    case ConditionType::BuffStacksCondition:
        return "BUFF_STACKS";
    case ConditionType::SpellCondition:
        return "SPELL";
    case ConditionType::ResourceCondition:
        return "RESOURCE";
    case ConditionType::VariableBuiltinCondition:
        return "BUILTIN VARIABLE";
    }

    return "<unknown condition type>";
}

QString Sentence::mathematical_symbol_as_string() const {
    switch (mathematical_symbol) {
    case Comparator::Eq:
        return "== (eq)";
    case Comparator::Geq:
        return ">= (geq)";
    case Comparator::Leq:
        return "<= (leq)";
    case Comparator::Less:
        return "< (less)";
    case Comparator::Greater:
        return "> (greater)";
    case Comparator::True:
        return "True (true_val)";
    case Comparator::False:
        return "False (false_val)";
    }

    return "<unknown mathematical symbol>";
}

QString Sentence::compared_value_type_as_string() const {
    switch (compared_value_type) {
    case CompareValueType::Boolean:
        return "bool";
    case CompareValueType::Float:
        return "float";
    }

    return "<unknown value type>";
}

void Sentence::dump() const {
    qDebug() << "logical_connective" << logical_connective_as_string();
    qDebug() << "condition_type" << condition_type_as_string();
    qDebug() << "type_value" << type_value;
    qDebug() << "mathematical symbol" << mathematical_symbol_as_string();
    qDebug() << "compared_value_type" << compared_value_type_as_string();
    qDebug() << "compared_value" << compared_value;
}

Condition::Condition(const Comparator comparator):
    comparator(comparator)
{}

QString Condition::comparator_as_string() const {
    switch (comparator) {
    case Comparator::Eq:
        return "==";
    case Comparator::Geq:
        return ">=";
    case Comparator::Leq:
        return "<=";
    case Comparator::Less:
        return "<";
    case Comparator::Greater:
        return ">";
    default:
        return "<unknown comparator>";
    }
}
