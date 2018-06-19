
#include "Condition.h"

#include <QDebug>

void Condition::dump() const {
    qDebug() << "logical_operator" << logical_operator;
    qDebug() << "type" << type;
    qDebug() << "type_value" << type_value;
    qDebug() << "compare" << compare;
    qDebug() << "cmp_value" << cmp_value;
}
