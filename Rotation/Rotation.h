#ifndef ROTATION_H
#define ROTATION_H

#include <QObject>
#include <QMap>
#include <QVector>

class CastIf;

class Rotation: public QObject {
    Q_OBJECT
public:
    Rotation(QObject* parent = 0);
    ~Rotation();

    void set_name(const QString name);
    void set_description(const QString desc);
    void add_variable(const QString var, const QString value);
    void add_prerequisite(const QString key, const QString value);
    void add_cast_if(CastIf* cast_if);
    void dump();

private:
    QString name;
    QString description;
    QMap<QString, QString> defined_variables;
    QMap<QString, QString> prerequisites;
    QVector<CastIf*> cast_ifs;
};

#endif // ROTATION_H
