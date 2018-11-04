#ifndef ROTATIONFILEREADER_H
#define ROTATIONFILEREADER_H

#include <QFile>
#include <QXmlStreamReader>
#include <QMap>
#include <QDebug>
#include <QVector>

class Rotation;
class RotationExecutor;
class Sentence;

class RotationFileReader {
public:
    RotationFileReader()
    {}

    void add_rotations(QVector<Rotation*>&);

private:
    Rotation* parse_rotation_file(const QString& path);
    void rotation_file_handler(QXmlStreamReader &reader, Rotation *rotation);
    bool rotation_executor_handler(QXmlStreamReader &reader, RotationExecutor* executor);

    bool evaluate_condition();
    bool add_type(Sentence* sentence, const QString& type_string);
    bool add_logical_connective(Sentence* sentence, const QString& logical_connective);
    bool add_compare_operation(Sentence* sentence, QString &compare_operation);
    bool add_let(Sentence* sentence, QStringList& let_list);

    int get_comparator_from_string(const QString& comparator) const;
};

#endif // ROTATIONFILEREADER_H
