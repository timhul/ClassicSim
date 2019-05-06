#include "SetBonusFileReader.h"

#include <QDebug>
#include <QDir>

void SetBonusFileReader::read_set_bonuses(const QString &path,
                                          QMap<int, QString>& possible_set_items,
                                          QMap<QString, QVector<QPair<int, QString>>>& set_bonus_tooltips) {
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Cannot read file" << path << ":" << file.errorString();
        return;
    }

    QXmlStreamReader reader(&file);

    if (reader.readNextStartElement()) {
        if (reader.name() == "sets")
            set_bonus_file_handler(reader, possible_set_items, set_bonus_tooltips);
        else
            qDebug() << "Did not find initial <sets> element in" << path;
    }

    file.close();
}

void SetBonusFileReader::set_bonus_file_handler(QXmlStreamReader &reader,
                                                QMap<int, QString>& possible_set_items,
                                                QMap<QString, QVector<QPair<int, QString>>>& set_bonus_tooltips) {
    while (reader.readNextStartElement()) {
        if (!reader.attributes().hasAttribute("name")) {
            qDebug() << "Missing name attribute for <set> element";
            for (const auto & attr : reader.attributes())
                qDebug() << attr.name() << attr.value();
            reader.skipCurrentElement();
            continue;
        }

        QString set_name = reader.attributes().value("name").toString();

        while (reader.readNextStartElement()) {
            if (reader.name() == "item_id") {
                if (!reader.attributes().hasAttribute("value")) {
                    qDebug() << QString("Missing 'value' attribute for <item_id> element in <set> '%1'").arg(set_name);
                    reader.skipCurrentElement();
                    continue;
                }
                int item_id = reader.attributes().value("value").toInt();

                if (possible_set_items.contains(item_id)) {
                    qDebug() << "item_id" << item_id << "part of two sets:" << possible_set_items[item_id] << "and" << set_name;
                    reader.skipCurrentElement();
                    continue;
                }

                possible_set_items[item_id] = set_name;
                reader.skipCurrentElement();
            }
            else if (reader.name() == "bonus") {
                if (!reader.attributes().hasAttribute("value")) {
                    qDebug() << QString("Missing 'value' attribute for <bonus> element in <set> '%1'").arg(set_name);
                    reader.skipCurrentElement();
                    continue;
                }

                int num_items = reader.attributes().value("value").toInt();

                if (!set_bonus_tooltips.contains(set_name))
                    set_bonus_tooltips[set_name] = {};

                bool duplicate = false;
                for (const auto & bonus_info : set_bonus_tooltips[set_name]) {
                    if (bonus_info.first == num_items) {
                        qDebug() << QString("Specified <bonus> value '%1' more than once in <set> '%2'").arg(num_items).arg(set_name);
                        duplicate = true;
                        break;
                    }
                }
                if (duplicate) {
                    reader.skipCurrentElement();
                    continue;
                }

                QString tooltip = reader.readElementText().simplified();
                set_bonus_tooltips[set_name].append({num_items, tooltip});
            }
            else
                reader.skipCurrentElement();
        }
    }
}
