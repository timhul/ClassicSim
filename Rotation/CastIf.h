#ifndef CASTIF_H
#define CASTIF_H

#include <QObject>
#include <QMap>
#include <QVector>

class Condition;

class CastIf: public QObject {
    Q_OBJECT
public:
    CastIf(QString name, QObject* parent = 0);
    ~CastIf();

    void add_condition(Condition* condition);
    QVector<Condition*>& get_conditions();

    void add_variable_assignment(QString var, QString value);
    QMap<QString, QString>& get_variable_assignments();

    void dump();

private:
    QString name;
    QVector<Condition*> conditions;
    QMap<QString, QString> variable_assignments;
};

#endif // CASTIF_H
