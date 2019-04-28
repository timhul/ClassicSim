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

namespace ConditionTypes {
    static const int BuffCondition = 0;
    static const int SpellCondition = 1;
    static const int ResourceCondition = 2;
    static const int VariableBuiltinCondition = 3;
}

namespace LogicalConnectives {
    static const int AND = 0;
    static const int OR = 1;
}

class Sentence {
public:
    int logical_connective;
    int condition_type;
    QString type_value;
    int mathematical_symbol;
    int compared_value_type;
    QString compared_value;

    QString logical_connective_as_string() const;
    QString condition_type_as_string() const;
    QString mathematical_symbol_as_string() const;
    QString compared_value_type_as_string() const;

    void dump() const;
};

class Condition {
public:
    Condition(int comparator);
    virtual ~Condition() = default;

    virtual bool condition_fulfilled() const = 0;
    virtual QString condition_description() const = 0;

    const int comparator;

protected:
    QString comparator_as_string() const;
};

#endif // CONDITION_H
