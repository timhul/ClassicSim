#include "Condition.h"

#include <QDebug>

QString Sentence::logical_connective_as_string() const {
    switch (logical_connective) {
    case LogicalConnectives::AND:
        return "AND";
    case LogicalConnectives::OR:
        return "OR";
    default:
        return QString("<unknown> '%1'").arg(logical_connective);
    }
}

QString Sentence::condition_type_as_string() const  {
    switch (condition_type) {
    case ConditionTypes::BuffCondition:
        return "BUFF";
    case ConditionTypes::SpellCondition:
        return "SPELL";
    case ConditionTypes::ResourceCondition:
        return "RESOURCE";
    case ConditionTypes::VariableAssignment:
        return "VARIABLE ASSIGNMENT";
    case ConditionTypes::VariableBuiltinCondition:
        return "BUILTIN VARIABLE";
    default:
        return QString("<unknown> '%1'").arg(condition_type);
    }
}

QString Sentence::mathematical_symbol_as_string() const {
    switch (mathematical_symbol) {
    case Comparators::eq:
        return "== (eq)";
    case Comparators::geq:
        return ">= (geq)";
    case Comparators::leq:
        return "<= (leq)";
    case Comparators::less:
        return "< (less)";
    case Comparators::greater:
        return "> (greater)";
    case Comparators::true_val:
        return "True (true_val)";
    case Comparators::false_val:
        return "False (false_val)";
    default:
        return QString("<unknown> '%1'").arg(mathematical_symbol);
    }
}

QString Sentence::compared_value_type_as_string() const {
    switch (compared_value_type) {
    case CompareValueTypes::bool_val:
        return "bool";
    case CompareValueTypes::float_val:
        return "float";
    default:
        return QString("<unknown> '%1'").arg(compared_value_type);
    }
}

void Sentence::dump() const {
    qDebug() << "logical_connective" << logical_connective_as_string();
    qDebug() << "condition_type" << condition_type_as_string();
    qDebug() << "type_value" << type_value;
    qDebug() << "mathematical symbol" << mathematical_symbol_as_string();
    qDebug() << "compared_value_type" << compared_value_type_as_string();
    qDebug() << "compared_value" << compared_value;
}

Condition::Condition(int comparator):
    comparator(comparator)
{}

QString Condition::comparator_as_string() const {
    switch (comparator) {
    case Comparators::eq:
        return "==";
    case Comparators::geq:
        return ">=";
    case Comparators::leq:
        return "<=";
    case Comparators::less:
        return "<";
    case Comparators::greater:
        return ">";
    default:
        return "<unknown comparator>";
    }
}
