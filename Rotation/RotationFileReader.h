#pragma once

#include <QFile>
#include <QXmlStreamReader>
#include <QMap>
#include <QVector>

class Rotation;
class RotationExecutor;
class Sentence;

enum class Comparator: int;

class RotationFileReader {
public:
    static void add_rotations(QVector<Rotation*>&);

private:
    static Rotation* parse_rotation_file(const QString& path);
    static void rotation_file_handler(QXmlStreamReader &reader, Rotation *rotation);
    static bool rotation_executor_handler(QXmlStreamReader &reader, RotationExecutor* executor);

    static bool evaluate_condition();
    static bool add_type(Sentence* sentence, const QString& type_string);
    static bool add_logical_connective(Sentence* sentence, const QString& logical_connective);
    static bool add_compare_operation(Sentence* sentence, QString &compare_operation);

    static Comparator get_comparator_from_string(const QString& comparator);
};
