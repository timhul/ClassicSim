#ifndef CONDITION_H
#define CONDITION_H

#include <QString>

class Condition {
  public:
    QString logical_operator;
    QString type;
    QString type_value;
    QString compare;
    QString cmp_value;

    void dump() const;
};

#endif // CONDITION_H
