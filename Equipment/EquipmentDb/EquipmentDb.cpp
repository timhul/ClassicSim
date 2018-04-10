
#include "EquipmentDb.h"
#include <QDebug>
#include <QDir>

EquipmentDb::EquipmentDb(QObject* parent):
    QObject(parent)
{
    QFile file("paths.xml");

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Cannot read file:" << file.errorString();
        qDebug() << QDir().currentPath();
        exit(0);
    }

    QXmlStreamReader reader(&file);

    QVector<QString> equipment_file_paths;

    if (reader.readNextStartElement()) {
        if (reader.name() != "paths") {
            qDebug() << "Expected <paths> root element in paths.xml.";
            return;
        }

        while (reader.readNextStartElement()) {
            if (reader.name() == "file") {
                QXmlStreamAttributes attrs = reader.attributes();
                if (attrs.hasAttribute("path"))
                    equipment_file_paths.append(attrs.value("path").toString());

                reader.skipCurrentElement();
            }
            else {
                qDebug() << "Skipping element" << reader.readElementText();
                reader.skipCurrentElement();
            }
        }
    }
    else
        qDebug() << "Failed to read paths.xml.";

    file.close();

    if (equipment_file_paths.empty())
        qDebug() << "Failed to find equipment files in paths.xml";

    for (int i = 0; i < equipment_file_paths.size(); ++i) {
        read_equipment_file(equipment_file_paths[i]);
    }
}

void EquipmentDb::read_equipment_file(const QString &path) {
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Cannot read file:" << file.errorString();
        return;
    }

    QXmlStreamReader reader(&file);

    if (reader.readNextStartElement()) {
        if (reader.name() == "weapons")
            weapon_file_handler(reader);
    }


    file.close();
}

void EquipmentDb::weapon_file_handler(QXmlStreamReader &reader) {
    while (reader.readNextStartElement()) {
        if (reader.name() == "weapon") {
            QMap<QString, QString> item;
            QVector<QMap<QString, QString>> procs;
            QXmlStreamAttributes attrs = reader.attributes();

            if (!attrs.hasAttribute("name")) {
                qDebug() << "Missing name attribute on weapon element";
                reader.skipCurrentElement();
                continue;
            }
            item["name"] = attrs.value("name").toString();
            qDebug() << "Processing" << reader.name() << reader.attributes().value("name").toString();

            while (reader.readNextStartElement()) {
                while (reader.readNextStartElement()) {
                    if (reader.name() == "info") {
                        info_element_reader(reader.attributes(), item);
                        reader.skipCurrentElement();
                    }
                    else if (reader.name() == "dmg_range") {
                        dmg_range_element_reader(reader.attributes(), item);
                        reader.skipCurrentElement();
                    }
                    else if (reader.name() == "class_restriction") {
                        class_restriction_element_reader(reader.attributes(), item);
                        reader.skipCurrentElement();
                    }
                    else if (reader.name() == "stats") {
                        stats_element_reader(reader, item);
                    }
                    else if (reader.name() == "source") {
                        item["source"] = reader.readElementText().trimmed();
                    }
                    else if (reader.name() == "proc") {
                        proc_element_reader(reader, procs);
                    }
                    else
                        reader.skipCurrentElement();
                }

                if (!procs.empty()) {
                    qDebug() << procs;
                }
            }
        }
        else {
            qDebug() << "Skipping element" << reader.readElementText();
            reader.skipCurrentElement();
        }
    }
}

void EquipmentDb::info_element_reader(const QXmlStreamAttributes &attrs, QMap<QString, QString> &item) {
    QVector<QString> mandatory_attrs = {"type", "slot", "unique", "req_lvl", "item_lvl", "quality", "boe"};
    QVector<QString> optional_attrs = {"faction"};

    for (int i = 0; i < mandatory_attrs.size(); ++i)
        add_mandatory_attr(attrs, mandatory_attrs[i], item);

    for (int i = 0; i < optional_attrs.size(); ++i)
        add_attr(attrs, optional_attrs[i], item);
}

void EquipmentDb::dmg_range_element_reader(const QXmlStreamAttributes &attrs, QMap<QString, QString> &item) {
    QVector<QString> mandatory_attrs = {"min", "max", "speed"};

    for (int i = 0; i < mandatory_attrs.size(); ++i)
        add_mandatory_attr(attrs, mandatory_attrs[i], item);
}

void EquipmentDb::class_restriction_element_reader(const QXmlStreamAttributes &attrs, QMap<QString, QString> &item) {
    item["RESTRICTED_TO_" + attrs.value("class").toString()] = "true";
}

void EquipmentDb::stats_element_reader(QXmlStreamReader &reader, QMap<QString, QString> &item) {
    while (reader.readNextStartElement()) {
        QXmlStreamAttributes attrs = reader.attributes();
        if (reader.name() == "stat") {
            item[attrs.value("type").toString()] = attrs.value("value").toString();
        }
        reader.skipCurrentElement();
    }
}

void EquipmentDb::proc_element_reader(QXmlStreamReader &reader, QVector<QMap<QString, QString>> &procs) {
    while (reader.readNextStartElement()) {
        QXmlStreamAttributes attrs = reader.attributes();
        if (reader.name() == "spell") {
            QMap<QString, QString> map;
            add_mandatory_attr(attrs, "name", map);
            add_mandatory_attr(attrs, "rate", map);
            add_mandatory_attr(attrs, "internal_cd", map);
            add_mandatory_attr(attrs, "recursive", map);

            add_attr(attrs, "min", map);
            add_attr(attrs, "max", map);
            add_attr(attrs, "instant", map);
            add_attr(attrs, "duration", map);
            add_attr(attrs, "tick_rate", map);
            add_attr(attrs, "amount", map);
            procs.append(map);
        }
        reader.skipCurrentElement();
    }
}

void EquipmentDb::add_mandatory_attr(const QXmlStreamAttributes &attrs, const QString& attr, QMap<QString, QString> &item) {
    add_attr(attrs, attr, item);

    if (!item.contains(attr))
        qDebug() << "Missing" << attr << "attribute";
}

void EquipmentDb::add_attr(const QXmlStreamAttributes &attrs, const QString& attr, QMap<QString, QString> &item) {
    if (!attrs.hasAttribute(attr)) {
        return;
    }

    item[attr] = attrs.value(attr).toString();
}
