
#include "Rotation.h"
#include "CastIf.h"

#include <QDebug>

Rotation::Rotation(QObject* parent) :
    QObject(parent)
{}

Rotation::~Rotation() {
    for (int i = 0; i < cast_ifs.size(); ++i) {
        delete cast_ifs[i];
    }

    cast_ifs.clear();
}

void Rotation::set_name(const QString name) {
    this->name = name;
}

void Rotation::set_description(const QString desc) {
    this->description = desc;
}

void Rotation::add_variable(const QString var, const QString value) {
    this->defined_variables.insert(var, value);
}

void Rotation::add_prerequisite(const QString key, const QString value) {
    this->prerequisites.insert(key, value);
}

void Rotation::add_cast_if(CastIf* cast_if) {
    this->cast_ifs.append(cast_if);
}

void Rotation::dump() {
    qDebug() << "name" << name;
    qDebug() << "desc" << description;
    qDebug() << "defined_variables" << defined_variables;
    qDebug() << "prerequisites" << prerequisites;
    qDebug() << "cast_ifs:";
    for (int i = 0; i < cast_ifs.size(); ++i) {
        cast_ifs[i]->dump();
    }
}
