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
class Sentence;

class RotationFileReader: public QObject {
    Q_OBJECT
public:
    RotationFileReader(QObject* parent = nullptr):
        QObject(parent) {}

    Rotation* get_rotation(const QString &path);

private:
    void rotation_file_handler(QXmlStreamReader &reader, Rotation *rotation);
    bool cast_if_handler(QXmlStreamReader &reader, CastIf *cast_if);

    bool evaluate_condition();
    bool add_type(Sentence* sentence, const QString& type_string);
    bool add_logical_connective(Sentence* sentence, const QString& logical_connective);
    bool add_compare_operation(Sentence* sentence, QString &compare_operation);
    bool add_let(Sentence* sentence, QStringList& let_list);
};

#endif // ROTATIONFILEREADER_H
