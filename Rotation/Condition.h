#ifndef CONDITION_H
#define CONDITION_H

#include <QString>


namespace Comparators {
    static const int less = 0;
    static const int leq = 1;
    static const int eq = 2;
    static const int geq = 3;
    static const int greater = 4;
    static const int false_val = 5;
    static const int true_val = 6;
}

namespace CompareValueTypes {
    static const int bool_val = 0;
    static const int float_val = 1;
}

namespace LogicalConnectives {
    static const int AND = 0;
    static const int OR = 1;
}

namespace ConditionTypes {
    static const int BuffCondition = 0;
    static const int SpellCondition = 1;
    static const int ResourceCondition = 2;
    static const int VariableBuiltinCondition = 3;
    static const int VariableAssignment = 4;
}


class Sentence {
public:
    int logical_connective;
    int condition_type;
    QString type_value;
    int mathematical_symbol;
    int compared_value_type;
    QString compared_value;

    void dump() const;
};


class LogicalConnective {
public:
    int logical_connective;
};


class Condition {
public:
    virtual ~Condition();

    virtual bool condition_fulfilled() const = 0;
};

#endif // CONDITION_H
