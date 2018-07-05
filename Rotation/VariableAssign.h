#ifndef VARIABLEASSIGN_H
#define VARIABLEASSIGN_H

#include <QString>

class VariableAssign {
public:
    VariableAssign(QString id, bool value);

    QString get_id() const;
    bool get_variable_value() const;

private:
    QString id;
    bool value;
};

#endif // VARIABLEASSIGN_H
