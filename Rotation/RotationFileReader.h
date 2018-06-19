#ifndef ROTATIONFILEREADER_H
#define ROTATIONFILEREADER_H

#include <QObject>
#include <QFile>
#include <QXmlStreamReader>
#include <QMap>
#include <QDebug>
#include <QVector>

class Rotation;
class CastIf;
class Condition;

class RotationFileReader: public QObject {
    Q_OBJECT
public:
    RotationFileReader(QObject* parent = 0):
        QObject(parent) {}

    void read_cast_ifs(Rotation* rotation, const QString &path);

private:
    void rotation_file_handler(QXmlStreamReader &reader, Rotation *rotation);
    bool cast_if_handler(QXmlStreamReader &reader, CastIf *cast_if);

    bool evaluate_condition();
    bool add_type(Condition* condition, const QString& type_string);
    bool add_logical_operator(Condition* condition, const QString& logical_operator);
    bool add_compare_operation(Condition* condition, QString &logical_operation);
    bool add_let(Condition* condition, QStringList& let_list);
};

#endif // ROTATIONFILEREADER_H
