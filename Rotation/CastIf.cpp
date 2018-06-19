
#include "CastIf.h"
#include "Condition.h"

#include <QDebug>

CastIf::CastIf(QString name, QObject* parent) :
    QObject(parent),
    name(name)
{}

CastIf::~CastIf() {
    for (int i = 0; i < conditions.size(); ++i) {
        delete conditions[i];
    }

    conditions.clear();
}

void CastIf::add_condition(Condition* condition) {
    this->conditions.append(condition);
}

QVector<Condition*> &CastIf::get_conditions() {
    return this->conditions;
}

void CastIf::add_variable_assignment(QString var, QString value) {
    this->variable_assignments.insert(var, value);
}

QMap<QString, QString>& CastIf::get_variable_assignments() {
    return this->variable_assignments;
}

void CastIf::dump() {
    qDebug() << "variable assignments" << variable_assignments;
    qDebug() << "conditions:";
    for (int i = 0; i < conditions.size(); ++i) {
        qDebug() << "-----------";
        conditions.at(i)->dump();
    }
}
