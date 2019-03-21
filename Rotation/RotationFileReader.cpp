#include "RotationFileReader.h"

#include <QDebug>
#include <QDir>

#include "Condition.h"
#include "Rotation.h"
#include "RotationExecutor.h"
#include "Utils/Check.h"

void RotationFileReader::add_rotations(QVector<Rotation*> & rotations) {
    QFile paths_file("rotation_paths.xml");

    if (!paths_file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Cannot read file:" << paths_file.errorString();
        qDebug() << QDir::currentPath();
        exit(0);
    }

    QXmlStreamReader paths_reader(&paths_file);
    QVector<QString> equipment_file_paths;

    if (paths_reader.readNextStartElement()) {
        if (paths_reader.name() != "paths") {
            qDebug() << "Expected <paths> root element in rotation_paths.xml.";
            return;
        }

        while (paths_reader.readNextStartElement()) {
            if (paths_reader.name() == "file") {
                QXmlStreamAttributes attrs = paths_reader.attributes();
                if (attrs.hasAttribute("path"))
                    equipment_file_paths.append(attrs.value("path").toString());

                paths_reader.skipCurrentElement();
            }
            else {
                qDebug() << "Skipping element" << paths_reader.readElementText();
                paths_reader.skipCurrentElement();
            }
        }
    }
    else
        qDebug() << "Failed to read rotation_paths.xml.";

    paths_file.close();

    if (equipment_file_paths.empty())
        qDebug() << "Failed to find rotation files in rotation_paths.xml";

    for (auto & path : equipment_file_paths) {
        qDebug() << "Parsing rotation file" << path;
        Rotation* rotation = parse_rotation_file(path);
        if (rotation != nullptr)
            rotations.append(rotation);
    }
}

Rotation* RotationFileReader::parse_rotation_file(const QString& path) {
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Cannot read file" << path << ":" << file.errorString();
        return nullptr;
    }

    QXmlStreamReader reader(&file);

    Rotation* rotation = nullptr;

    if (reader.readNextStartElement() && reader.name() == "rotation") {
        if (!reader.attributes().hasAttribute("class")) {
            qDebug() << path << "missing 'class' attribute on <rotation> element";
            file.close();
            return rotation;
        }
        QString class_name = reader.attributes().value("class").toString();

        rotation = new Rotation(class_name);
        rotation_file_handler(reader, rotation);
    }

    file.close();

    return rotation;
}

void RotationFileReader::rotation_file_handler(QXmlStreamReader &reader, Rotation* rotation) {
    rotation->set_name(reader.attributes().value("name").toString());

    while (reader.readNextStartElement()) {
        if (reader.name() == "description") {
            rotation->set_description(reader.readElementText().simplified());
            continue;
        }

        if (reader.name() == "define_vars") {
            while (reader.readNextStartElement()) {
                if (reader.name() != "let") {
                    qDebug() << "<define_vars> missing <let> element";
                    reader.skipCurrentElement();
                    continue;
                }
                if (!reader.attributes().hasAttribute("variable")) {
                    qDebug() << "defined variables missing 'variable' attribute'";
                    reader.skipCurrentElement();
                    continue;
                }
                if (!reader.attributes().hasAttribute("equal")) {
                    qDebug() << "defined variables missing 'equal' attribute'";
                    reader.skipCurrentElement();
                    continue;
                }

                QString var_name = reader.attributes().value("variable").toString();
                QString var_value = reader.attributes().value("equal").toString();
                rotation->add_variable(var_name, var_value);
            }
            reader.skipCurrentElement();
            continue;
        }

        if (reader.name() == "prerequisites") {
            while (reader.readNextStartElement()) {
                QSet<QString> elements = {"talent", "patch_at_least", "patch_at_most"};
                if (!elements.contains(reader.name().toString())) {
                    qDebug() << "<prerequisites> missing any of elements" << elements;
                    reader.skipCurrentElement();
                    continue;
                }
                if (!reader.attributes().hasAttribute("name")) {
                    qDebug() << "prerequisites missing 'name' attribute'";
                    reader.skipCurrentElement();
                    continue;
                }
                rotation->add_prerequisite(reader.name().toString(),
                                           reader.attributes().value("name").toString());
                reader.skipCurrentElement();
            }
            continue;
        }

        if (reader.name() == "cast_if") {
            QString name = reader.attributes().value("name").toString();
            RotationExecutor* executor = new RotationExecutor(name);
            if (rotation_executor_handler(reader, executor)) {
                rotation->add_executor(executor);
            }
            else
                delete executor;
        }
    }
}

bool RotationFileReader::rotation_executor_handler(QXmlStreamReader &reader, RotationExecutor* executor) {
    QStringList expressions = reader.readElementText().trimmed().split('\n', QString::SkipEmptyParts);

    for (auto &str : expressions)
        str = str.trimmed();

    if (expressions.empty())
        return true;

    QString let_statement = "let";
    // First sentence does not have logical connective at start.
    // [TYPE] "[TYPE_VALUE]" [COMPARE_OPERATION]
    // Split into [TYPE, TYPE_VALUE, COMPARE_OPERATION]
    QStringList quotation_split = expressions.takeFirst().split('"', QString::SkipEmptyParts);
    for (auto &str : quotation_split)
        str = str.trimmed();

    if (quotation_split.size() < 2) {
        qDebug() << "Expected quotation marks" << quotation_split;
        return false;
    }

    auto* sentence = new Sentence();
    // Take TYPE or LET statement
    if (quotation_split[0].startsWith(let_statement)) {
        if (!add_let(sentence, quotation_split))
            return false;
    }
    else {
        if (!this->add_type(sentence, quotation_split.takeFirst()))
            return false;

        // Take TYPE_VALUE
        sentence->type_value = quotation_split.takeFirst();

        // Take COMPARE_OPERATION
        if (!quotation_split.empty()) {
            QString compare_operation = quotation_split.takeFirst();
            add_compare_operation(sentence, compare_operation);
            if (!quotation_split.empty()) {
                qDebug() << "Quotation split not empty after adding compare operation" << quotation_split;
                return false;
            }
        }
    }

    executor->add_sentence(sentence);

    for (int i = 0; i < expressions.size(); ++i) {
        quotation_split = expressions[i].split('"', QString::SkipEmptyParts);
        for (auto &str : quotation_split)
            str = str.trimmed();

        if (quotation_split.size() < 3) {
            qDebug() << "Expected quotation marks" << quotation_split;
            return false;
        }

        sentence = new Sentence();
        // Take LET statement if exists
        if (quotation_split[0].startsWith(let_statement)) {
            if (!add_let(sentence, quotation_split)) {
                delete sentence;
                return false;
            }

            executor->add_sentence(sentence);
            continue;
        }

        QStringList logical_connective_split = quotation_split.takeFirst().split(' ', QString::SkipEmptyParts);
        // Else LOGICAL CONNECTIVE
        if (logical_connective_split.size() != 2) {
            qDebug() << "Expected logical operator split size of 2, got:" << logical_connective_split;
            delete sentence;
            return false;
        }

        if (!this->add_logical_connective(sentence, logical_connective_split.takeFirst())) {
            delete sentence;
            return false;
        }

        // Take TYPE
        if (!this->add_type(sentence, logical_connective_split.takeFirst())) {
            delete sentence;
            return false;
        }

        // Take TYPE_VALUE
        sentence->type_value = quotation_split.takeFirst();

        // Take COMPARE_OPERATION
        if (!quotation_split.empty()) {
            QString compare_operation = quotation_split.takeFirst();
            add_compare_operation(sentence, compare_operation);
            if (!quotation_split.empty()) {
                qDebug() << "Quotation split not empty after adding compare operation" << quotation_split;
                delete sentence;
                return false;
            }
        }

        executor->add_sentence(sentence);
    }

    return true;
}

bool RotationFileReader::add_type(Sentence* sentence, const QString& type_string) {
    QMap<QString, int> acceptable_types = {{"spell", ConditionTypes::SpellCondition},
                                           {"buff", ConditionTypes::BuffCondition},
                                           {"resource", ConditionTypes::ResourceCondition},
                                           {"variable", ConditionTypes::VariableBuiltinCondition}};

    if (!acceptable_types.contains(type_string)) {
        qDebug() << "Expected type, got" << type_string;
        return false;
    }

    sentence->condition_type = acceptable_types.value(type_string);

    return true;
}

bool RotationFileReader::add_logical_connective(Sentence* sentence, const QString& logical_connective) {
    QSet<QString> logical_connective_strings = {"and", "or"};
    if (!logical_connective_strings.contains(logical_connective)) {
        qDebug() << "Expected logical connective, got" << logical_connective;
        return false;
    }

    sentence->logical_connective = logical_connective == "and" ? LogicalConnectives::AND :
                                                                 LogicalConnectives::OR;
    return true;
}

bool RotationFileReader::add_compare_operation(Sentence* sentence, QString& compare_operation) {
    QSet<QString> cmp_by_float = {"greater", "geq", "eq", "leq", "less"};
    QSet<QString> cmp_by_bool = {"is"};

    QStringList cmp_operation_split = compare_operation.split(' ', QString::SkipEmptyParts);
    if (cmp_operation_split.empty()) {
        qDebug() << "Compare operation split returned empty split";
        return false;
    }

    for (auto &str : cmp_operation_split)
        str = str.trimmed();

    // Sentence e.g. "buff 'Overpower' is false"
    // Sentence e.g. "buff 'Overpower' greater 2"
    if (cmp_operation_split.size() == 2) {
        QString cmp = cmp_operation_split.takeFirst();
        if (!cmp_by_float.contains(cmp) && !cmp_by_bool.contains(cmp)) {
            qDebug() << "Invalid left hand side:" << cmp;
            return false;
        }

        // is [true/false]
        if (cmp_by_bool.contains(cmp)) {
            QSet<QString> accepted_vals = {"true", "false"};
            QString compare_value = cmp_operation_split.takeFirst();
            if (!accepted_vals.contains(compare_value)) {
                qDebug() << "Invalid right hand side value for 'is':" << compare_value;
                return false;
            }

            sentence->mathematical_symbol = Comparators::eq;
            sentence->compared_value_type = CompareValueTypes::bool_val;
            sentence->compared_value = compare_value;
            return true;
        }

        // [greater/geq/eq/leq/less] [0-9]
        sentence->mathematical_symbol = get_comparator_from_string(cmp);
        sentence->compared_value_type = CompareValueTypes::float_val;
        sentence->compared_value = cmp_operation_split.takeFirst();
        return true;
    }

    qDebug() << "Unexpected logical operation split" << cmp_operation_split;
    return false;
}

bool RotationFileReader::add_let(Sentence* sentence, QStringList &let_list) {
    if (let_list.size() != 3) {
        qDebug() << "Failed to parse let statement:" << let_list;
        return false;
    }

    sentence->condition_type = ConditionTypes::VariableAssignment;
    sentence->type_value = let_list[1];
    sentence->compared_value = let_list[2].split(' ', QString::SkipEmptyParts).takeLast();

    return true;
}

int RotationFileReader::get_comparator_from_string(const QString& comparator) const {
    if (comparator == "greater")
        return Comparators::greater;
    if (comparator == "geq")
        return Comparators::geq;
    if (comparator == "eq")
        return Comparators::eq;
    if (comparator == "leq")
        return Comparators::leq;
    if (comparator == "less")
        return Comparators::less;

    check(false, QString("Could not find comparator for '%1'").arg(comparator).toStdString());
    return -1;
}
