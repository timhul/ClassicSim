
#include "Condition.h"

#include <QDebug>

Condition::~Condition() {

}

void Sentence::dump() const {
    qDebug() << "logical_operator" << logical_connective;
    qDebug() << "type" << condition_type;
    qDebug() << "type_value" << type_value;
    qDebug() << "compare" << mathematical_symbol;
    qDebug() << "cmp_value" << compared_value;
}
