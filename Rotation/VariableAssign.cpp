
#include "VariableAssign.h"

#include <utility>

VariableAssign::VariableAssign(QString id, bool value) :
    id(std::move(id)),
    value(value)
{}

QString VariableAssign::get_id() const {
    return this->id;
}

bool VariableAssign::get_variable_value() const {
    return this->value;
}
