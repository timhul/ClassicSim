
#include "RotationFileReader.h"
#include "Rotation.h"
#include "CastIf.h"
#include "Condition.h"

#include <QDebug>
#include <QDir>

void RotationFileReader::read_cast_ifs(Rotation *rotation, const QString &path) {
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Cannot read file" << path << ":" << file.errorString();
        return;
    }

    QXmlStreamReader reader(&file);

    if (reader.readNextStartElement() && reader.name() == "rotation")
        rotation_file_handler(reader, rotation);

    file.close();
}

void RotationFileReader::rotation_file_handler(QXmlStreamReader &reader, Rotation* rotation) {
    rotation->set_name(reader.name().toString());

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
            CastIf* cast_if = new CastIf(name);
            if (cast_if_handler(reader, cast_if) == true) {
                rotation->add_cast_if(cast_if);
            }
            else
                delete cast_if;
        }
    }
}

bool RotationFileReader::cast_if_handler(QXmlStreamReader &reader, CastIf* cast_if) {    
    QStringList expressions = reader.readElementText().trimmed().split('\n', QString::SkipEmptyParts);

    for (auto &str : expressions)
        str = str.trimmed();

    if (expressions.empty())
        return true;

    QString let_statement = "let";
    // First entry does not have chain logical operator at start.
    // [TYPE] "[TYPE_VALUE]" [COMPARE_OPERATION]
    // Split into [TYPE, TYPE_VALUE, COMPARE_OPERATION]
    QStringList quotation_split = expressions.takeFirst().split('"', QString::SkipEmptyParts);
    for (auto &str : quotation_split)
        str = str.trimmed();

    if (quotation_split.size() < 2) {
        qDebug() << "Expected quotation marks" << quotation_split;
        return false;
    }

    Condition* condition = new Condition();
    // Take TYPE or LET statement
    if (quotation_split[0].startsWith(let_statement) == true) {
        if (add_let(condition, quotation_split) == false)
            return false;
    }
    else {
        if (this->add_type(condition, quotation_split.takeFirst()) == false)
            return false;

        // Take TYPE_VALUE
        condition->type_value = quotation_split.takeFirst();

        // Take COMPARE_OPERATION
        if (!quotation_split.empty()) {
            QString compare_operation = quotation_split.takeFirst();
            add_compare_operation(condition, compare_operation);
            if (!quotation_split.empty()) {
                qDebug() << "Quotation split not empty after adding compare operation" << quotation_split;
                return false;
            }
        }
    }

    cast_if->add_condition(condition);

    for (int i = 0; i < expressions.size(); ++i) {
        quotation_split = expressions[i].split('"', QString::SkipEmptyParts);
        for (auto &str : quotation_split)
            str = str.trimmed();

        if (quotation_split.size() < 3) {
            qDebug() << "Expected quotation marks" << quotation_split;
            return false;
        }

        condition = new Condition();
        // Take LET statement if exists
        if (quotation_split[0].startsWith(let_statement) == true) {
            if (add_let(condition, quotation_split) == false) {
                delete condition;
                return false;
            }

            cast_if->add_condition(condition);
            continue;
        }

        QStringList logical_operator_split = quotation_split.takeFirst().split(' ', QString::SkipEmptyParts);
        // Else LOGICAL OPERATOR
        if (logical_operator_split.size() != 2) {
            qDebug() << "Expected logical operator split size of 2, got:" << logical_operator_split;
            delete condition;
            return false;
        }

        if (this->add_logical_operator(condition, logical_operator_split.takeFirst()) == false) {
            delete condition;
            return false;
        }

        // Take TYPE
        if (this->add_type(condition, logical_operator_split.takeFirst()) == false) {
            delete condition;
            return false;
        }

        // Take TYPE_VALUE
        condition->type_value = quotation_split.takeFirst();

        // Take COMPARE_OPERATION
        if (!quotation_split.empty()) {
            QString compare_operation = quotation_split.takeFirst();
            add_compare_operation(condition, compare_operation);
            if (!quotation_split.empty()) {
                qDebug() << "Quotation split not empty after adding compare operation" << quotation_split;
                delete condition;
                return false;
            }
        }

        cast_if->add_condition(condition);
    }

    return true;
}

bool RotationFileReader::add_type(Condition *condition, const QString& type_string) {
    QSet<QString> acceptable_types = {"spell", "buff", "resource", "variable"};

    if (!acceptable_types.contains(type_string)) {
        qDebug() << "Expected type, got" << type_string;
        return false;
    }

    condition->type = type_string;

    return true;
}

bool RotationFileReader::add_logical_operator(Condition *condition, const QString& logical_operator) {
    QSet<QString> logical_operators = {"and", "or"};
    if (!logical_operators.contains(logical_operator)) {
        qDebug() << "Expected logical operator, got" << logical_operator;
        return false;
    }

    condition->logical_operator = logical_operator;
    return true;
}

bool RotationFileReader::add_compare_operation(Condition *condition, QString& logical_operation) {
    QSet<QString> cmp_by_following_value = {"greater", "less"};
    QSet<QString> cmp_immediate = {"true", "false"};

    QStringList logical_operation_split = logical_operation.split(' ', QString::SkipEmptyParts);
    if (logical_operation_split.empty()) {
        qDebug() << "Logical operation split returned empty split";
        return false;
    }

    for (auto &str : logical_operation_split)
        str = str.trimmed();

    if (logical_operation_split.size() == 1) {
        QString cmp = logical_operation_split.takeFirst();
        if (!cmp_immediate.contains(cmp)) {
            qDebug() << "Expected immediate compare value:" << cmp;
            return false;
        }

        condition->compare = "equal";
        condition->cmp_value = cmp;
        return true;
    }

    if (logical_operation_split.size() == 2) {
        QString cmp = logical_operation_split.takeFirst();
        if (!cmp_by_following_value.contains(cmp)) {
            qDebug() << "Invalid left hand side operator:" << cmp;
            return false;
        }

        condition->compare = cmp;
        condition->cmp_value = logical_operation_split.takeFirst();
        return true;
    }

    qDebug() << "Unexpected logical operation split" << logical_operation_split;
    return false;
}

bool RotationFileReader::add_let(Condition *condition, QStringList &let_list) {
    if (let_list.size() != 3) {
        qDebug() << "Failed to parse let statement:" << let_list;
        return false;
    }
    condition->type = let_list[0];
    condition->type_value = let_list[1];
    condition->cmp_value = let_list[2].split(' ', QString::SkipEmptyParts).takeLast();

    return true;
}
