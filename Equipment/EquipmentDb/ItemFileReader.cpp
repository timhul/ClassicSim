#include "ItemFileReader.h"

#include <QDebug>
#include <QDir>

#include "Item.h"
#include "WeaponFileReader.h"

ItemFileReader::ItemFileReader(QObject* parent):
    QObject(parent)
{}

void ItemFileReader::read_items(QVector<Item *> &items, const QString &path) {
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Cannot read file" << path << ":" << file.errorString();
        return;
    }

    QXmlStreamReader reader(&file);

    if (reader.readNextStartElement()) {
        if (reader.name() == "items")
            item_file_handler(reader, items);
        if (reader.name() == "weapons")
            WeaponFileReader().weapon_file_handler(reader, items);
    }

    file.close();
}

void ItemFileReader::item_file_handler(QXmlStreamReader &reader, QVector<Item*> &items) {
    while (reader.readNextStartElement()) {
        QString classification = reader.name().toString();

        if (!reader.attributes().hasAttribute("id")) {
            qDebug() << "Missing id attribute";
            for (auto & attr : reader.attributes().toList())
                qDebug() << attr.name() << attr.value();
            reader.skipCurrentElement();
            continue;
        }
        QString id = reader.attributes().value("id").toString();

        while (reader.readNextStartElement()) {
            if (reader.name() != "patch") {
                qDebug() << "Skipping element" << reader.name();
                reader.skipCurrentElement();
                continue;
            }
            QMap<QString, QString> item_map;
            QVector<QPair<QString, QString>> stats;
            QVector<QMap<QString, QString>> procs;
            QVector<QMap<QString, QString>> uses;
            item_map["classification"] = classification;
            item_map["id"] = id;
            item_map["patch"] = reader.attributes().value("name").toString();

            while (reader.readNextStartElement()) {
                if (reader.name() == "info") {
                    info_element_reader(reader.attributes(), item_map);
                    reader.skipCurrentElement();
                }
                else if (reader.name() == "class_restriction") {
                    class_restriction_element_reader(reader.attributes(), item_map);
                    reader.skipCurrentElement();
                }
                else if (reader.name() == "stats") {
                    stats_element_reader(reader, stats);
                }
                else if (reader.name() == "source") {
                    item_map["source"] = reader.readElementText().trimmed();
                }
                else if (reader.name() == "proc") {
                    proc_element_reader(reader, procs);
                }
                else if (reader.name() == "uses") {
                    use_element_reader(reader, uses);
                }
                else if (reader.name() == "flavour_text") {
                    item_map["flavour_text"] = reader.readElementText().simplified();
                }
                else if (reader.name() == "special_equip_effect") {
                    item_map["special_equip_effect"] = reader.readElementText().simplified();
                }
                else
                    reader.skipCurrentElement();
            }

            create_item(items, item_map, stats, procs, uses);
            item_map.remove("classification");
            warn_remaining_keys(item_map);
        }
    }
}

void ItemFileReader::info_element_reader(const QXmlStreamAttributes &attrs, QMap<QString, QString> &item) {
    QVector<QString> mandatory_attrs = {"name", "type", "slot", "unique", "req_lvl", "item_lvl", "quality", "boe"};
    QVector<QString> optional_attrs = {"faction", "icon"};

    for (const auto & mandatory_attr : mandatory_attrs)
        add_mandatory_attr(attrs, mandatory_attr, item);

    for (const auto & optional_attr : optional_attrs)
        add_attr(attrs, optional_attr, item);
}

void ItemFileReader::class_restriction_element_reader(const QXmlStreamAttributes &attrs, QMap<QString, QString> &item) {
    item["RESTRICTED_TO_" + attrs.value("class").toString()] = "true";
}

void ItemFileReader::stats_element_reader(QXmlStreamReader &reader, QVector<QPair<QString, QString>> &stats) {
    while (reader.readNextStartElement()) {
        QXmlStreamAttributes attrs = reader.attributes();
        if (reader.name() == "stat") {
            stats.append(QPair<QString, QString>(attrs.value("type").toString(), attrs.value("value").toString()));
        }
        reader.skipCurrentElement();
    }
}

void ItemFileReader::proc_element_reader(QXmlStreamReader &reader, QVector<QMap<QString, QString>> &procs) {
    while (reader.readNextStartElement()) {
        QXmlStreamAttributes attrs = reader.attributes();
        if (reader.name() == "spell") {
            QMap<QString, QString> map;
            add_mandatory_attr(attrs, "name", map);
            add_mandatory_attr(attrs, "rate", map);
            add_mandatory_attr(attrs, "internal_cd", map);

            add_attr(attrs, "min", map);
            add_attr(attrs, "max", map);
            add_attr(attrs, "instant", map);
            add_attr(attrs, "duration", map);
            add_attr(attrs, "tick_rate", map);
            add_attr(attrs, "amount", map);
            add_attr(attrs, "max_stacks", map);
            add_attr(attrs, "value", map);
            procs.append(map);
        }
        reader.skipCurrentElement();
    }
}

void ItemFileReader::use_element_reader(QXmlStreamReader &reader, QVector<QMap<QString, QString>> &uses) {
    while (reader.readNextStartElement()) {
        QXmlStreamAttributes attrs = reader.attributes();
        if (reader.name() == "use") {
            QMap<QString, QString> map;
            add_mandatory_attr(attrs, "name", map);

            add_attr(attrs, "cooldown", map);
            add_attr(attrs, "type", map);
            add_attr(attrs, "value", map);
            add_attr(attrs, "duration", map);
            uses.append(map);
        }
        reader.skipCurrentElement();
    }
}

void ItemFileReader::add_mandatory_attr(const QXmlStreamAttributes &attrs, const QString& attr, QMap<QString, QString> &item) {
    add_attr(attrs, attr, item);

    if (!item.contains(attr))
        qDebug() << "Missing" << attr << "attribute";
}

void ItemFileReader::add_attr(const QXmlStreamAttributes &attrs, const QString& attr, QMap<QString, QString> &item) {
    if (!attrs.hasAttribute(attr)) {
        return;
    }

    item[attr] = attrs.value(attr).toString();
}

void ItemFileReader::create_item(QVector<Item*> &items,
                                 QMap<QString, QString> &item_map,
                                 QVector<QPair<QString, QString>> &stats,
                                 QVector<QMap<QString, QString>> &procs,
                                 QVector<QMap<QString, QString>> &uses) {
    QVector<QString> mandatory_attrs = {"id", "name", "classification", "patch", "type", "slot",
                                        "unique", "req_lvl", "item_lvl", "quality", "boe"};

    bool missing_attrs = false;
    for (const auto & mandatory_attr : mandatory_attrs) {
        if (!item_map.contains(mandatory_attr)) {
            qDebug() << "Missing mandatory base attribute" << mandatory_attr;
            missing_attrs = true;
        }
    }

    if (missing_attrs)
        return;

    QMap<QString, QString> info;
    extract_info(item_map, info);

    items.append(new Item(info["name"], stats, info, procs, uses));

    QVector<QString> handled_keys = {"id"};

    for (const auto & handled_key : handled_keys) {
        item_map.remove(handled_key);
    }
}

void ItemFileReader::extract_info(QMap<QString, QString> &item, QMap<QString, QString> &info) {
    QVector<QString> keys = {"name", "patch", "type", "slot", "boe", "item_lvl", "req_lvl", "faction", "unique", "quality", "source", "icon",
                             "RESTRICTED_TO_WARRIOR", "RESTRICTED_TO_PALADIN", "RESTRICTED_TO_HUNTER",
                             "RESTRICTED_TO_ROGUE", "flavour_text", "special_equip_effect"};

    extract(keys, item, info);
}

void ItemFileReader::extract(QVector<QString> handled_keys, QMap<QString, QString> &source, QMap<QString, QString> &target) {
    for (const auto& key : handled_keys) {
        if (source.contains(key)) {
            target[key] = source.take(key);
        }
    }
}

void ItemFileReader::warn_remaining_keys(QMap<QString, QString> &item) {
    QMap<QString, QString>::const_iterator it = item.constBegin();
    auto end = item.constEnd();
    while(it != end) {
        qDebug() << "Warning: Unhandled key" << QString("%1: %2").arg(it.key(), it.value());
        ++it;
    }
}
