#include "RotationFileReader.h"

#include <QDebug>
#include <QDir>

#include "Condition.h"
#include "Rotation.h"
#include "RotationExecutor.h"
#include "Spell.h"
#include "Utils/Check.h"

void RotationFileReader::add_rotations(QVector<Rotation*>& rotations) {
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
            } else {
                qDebug() << "Skipping element" << paths_reader.readElementText();
                paths_reader.skipCurrentElement();
            }
        }
    } else
        qDebug() << "Failed to read rotation_paths.xml.";

    paths_file.close();

    if (equipment_file_paths.empty())
        qDebug() << "Failed to find rotation files in rotation_paths.xml";

    for (const auto& path : equipment_file_paths) {
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

void RotationFileReader::rotation_file_handler(QXmlStreamReader& reader, Rotation* rotation) {
    rotation->set_name(reader.attributes().value("name").toString());

    if (!rotation->try_set_attack_mode(reader.attributes().value("attack_mode").toString()))
        qDebug() << "Failed to set attack mode for" << rotation->get_name();

    while (reader.readNextStartElement()) {
        if (reader.name() == "description") {
            rotation->set_description(reader.readElementText().simplified());
            continue;
        }

        if (reader.name() == "precombat_actions") {
            QSet<QString> elements = {"spell", "precast_spell"};
            while (reader.readNextStartElement()) {
                QString element_name = reader.name().toString();
                if (!elements.contains(element_name)) {
                    qDebug() << "<precombat_actions> has unknown element" << element_name;
                    reader.skipCurrentElement();
                    continue;
                }
                if (!reader.attributes().hasAttribute("name")) {
                    qDebug() << "<precombat_actions> element" << element_name << "missing 'name' attribute'";
                    reader.skipCurrentElement();
                    continue;
                }
                if (element_name == "spell")
                    rotation->add_precombat_spell(reader.attributes().value("name").toString());
                else
                    rotation->add_precast_spell(reader.attributes().value("name").toString());
                reader.skipCurrentElement();
            }

            continue;
        }

        if (reader.name() == "cast_if") {
            QString name = reader.attributes().value("name").toString();
            const int spell_rank = reader.attributes().hasAttribute("rank") ? reader.attributes().value("rank").toInt() : Spell::MAX_RANK;
            RotationExecutor* executor = new RotationExecutor(name, spell_rank);
            if (rotation_executor_handler(reader, executor)) {
                rotation->add_executor(executor);
            } else
                delete executor;
        }
    }
}

bool RotationFileReader::rotation_executor_handler(QXmlStreamReader& reader, RotationExecutor* executor) {
    QStringList expressions = reader.readElementText().trimmed().split('\n', Qt::SkipEmptyParts);

    for (auto& str : expressions)
        str = str.trimmed();

    if (expressions.empty())
        return true;

    // First sentence does not have logical connective at start.
    // [TYPE] "[TYPE_VALUE]" [COMPARE_OPERATION]
    // Split into [TYPE, TYPE_VALUE, COMPARE_OPERATION]
    QStringList quotation_split = expressions.takeFirst().split('"', Qt::SkipEmptyParts);
    for (auto& str : quotation_split)
        str = str.trimmed();

    if (quotation_split.size() < 2) {
        qDebug() << "Expected quotation marks" << quotation_split;
        return false;
    }

    auto sentence = new Sentence();
    // Take TYPE statement
    if (!add_type(sentence, quotation_split.takeFirst())) {
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

    for (int i = 0; i < expressions.size(); ++i) {
        quotation_split = expressions[i].split('"', Qt::SkipEmptyParts);
        for (auto& str : quotation_split)
            str = str.trimmed();

        if (quotation_split.size() < 3) {
            qDebug() << "Expected quotation marks" << quotation_split;
            delete sentence;
            return false;
        }

        sentence = new Sentence();

        QStringList logical_connective_split = quotation_split.takeFirst().split(' ', Qt::SkipEmptyParts);
        // Else LOGICAL CONNECTIVE
        if (logical_connective_split.size() != 2) {
            qDebug() << "Expected logical operator split size of 2, got:" << logical_connective_split;
            delete sentence;
            return false;
        }

        if (!add_logical_connective(sentence, logical_connective_split.takeFirst())) {
            delete sentence;
            return false;
        }

        // Take TYPE
        if (!add_type(sentence, logical_connective_split.takeFirst())) {
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
    QMap<QString, ConditionType> acceptable_types = {{"spell", ConditionType::SpellCondition},
                                                     {"buff_duration", ConditionType::BuffDurationCondition},
                                                     {"buff_stacks", ConditionType::BuffStacksCondition},
                                                     {"resource", ConditionType::ResourceCondition},
                                                     {"variable", ConditionType::VariableBuiltinCondition}};

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

    sentence->logical_connective = logical_connective == "and" ? LogicalConnective::AND : LogicalConnective::OR;
    return true;
}

bool RotationFileReader::add_compare_operation(Sentence* sentence, QString& compare_operation) {
    QSet<QString> cmp_by_float = {"greater", "geq", "eq", "leq", "less"};
    QSet<QString> cmp_by_bool = {"is"};

    QStringList cmp_operation_split = compare_operation.split(' ', Qt::SkipEmptyParts);
    if (cmp_operation_split.empty()) {
        qDebug() << "Compare operation split returned empty split";
        return false;
    }

    for (auto& str : cmp_operation_split)
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

            sentence->mathematical_symbol = Comparator::Eq;
            sentence->compared_value_type = CompareValueType::Boolean;
            sentence->compared_value = compare_value;
            return true;
        }

        // [greater/geq/eq/leq/less] [0-9]
        sentence->mathematical_symbol = get_comparator_from_string(cmp);
        sentence->compared_value_type = CompareValueType::Float;
        sentence->compared_value = cmp_operation_split.takeFirst();
        return true;
    }

    qDebug() << "Unexpected logical operation split" << cmp_operation_split;
    return false;
}

Comparator RotationFileReader::get_comparator_from_string(const QString& comparator) {
    if (comparator == "greater")
        return Comparator::Greater;
    if (comparator == "geq")
        return Comparator::Geq;
    if (comparator == "eq")
        return Comparator::Eq;
    if (comparator == "leq")
        return Comparator::Leq;
    if (comparator == "less")
        return Comparator::Less;

    check(false, QString("Could not find comparator for '%1'").arg(comparator).toStdString());
    return Comparator::False;
}
