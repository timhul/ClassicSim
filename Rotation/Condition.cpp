
#include "Condition.h"

#include <QDebug>

Condition::~Condition() = default;

void Sentence::dump() const {
    qDebug() << "logical_connective" << logical_connective;
    qDebug() << "condition_type" << condition_type;
    qDebug() << "type_value" << type_value;
    qDebug() << "mathematical symbol" << mathematical_symbol;
    qDebug() << "compared_value_type" << compared_value_type;
    qDebug() << "compared_value" << compared_value;
}
