#include "ProjectileFileReader.h"

#include <QDebug>

#include "Projectile.h"

void ProjectileFileReader::file_handler(QXmlStreamReader &reader, QVector<Item*> &items) {
    while (reader.readNextStartElement()) {
        if (reader.name() == "projectile") {
            QString classification = reader.name().toString();

            if (!reader.attributes().hasAttribute("id")) {
                qDebug() << "Missing id attribute on projectile element";
                reader.skipCurrentElement();
                continue;
            }
            QString id = reader.attributes().value("id").toString();

            QMap<QString, QString> item_map;
            item_map["classification"] = classification;
            item_map["id"] = id;
            item_map["phase"] = reader.attributes().value("phase").toString();
            QSet<int> mutex_item_ids;

            while (reader.readNextStartElement()) {
                if (reader.name() == "info") {
                    info_element_reader(reader.attributes(), item_map);
                    reader.skipCurrentElement();
                }
                else if (reader.name() == "dps") {
                    dps_element_reader(reader.attributes(), item_map);
                    reader.skipCurrentElement();
                }
                else if (reader.name() == "source") {
                    item_map["source"] = reader.readElementText().trimmed();
                }
                else if (reader.name() == "mutex") {
                    mutex_element_reader(reader.attributes(), mutex_item_ids);
                    reader.skipCurrentElement();
                }
                else
                    reader.skipCurrentElement();
            }

            create_projectile(items, item_map, mutex_item_ids);
            item_map.remove("classification");
            warn_remaining_keys(item_map);
        }
        else {
            qDebug() << "Skipping element" << reader.name();
            reader.skipCurrentElement();
        }
    }
}

void ProjectileFileReader::dps_element_reader(const QXmlStreamAttributes &attrs, QMap<QString, QString> &item) {
    QVector<QString> mandatory_attrs = {"value"};

    for (const auto & mandatory_attr : mandatory_attrs)
        add_mandatory_attr(attrs, mandatory_attr, item);
}

void ProjectileFileReader::create_projectile(QVector<Item*> &items, QMap<QString, QString>& item_map, QSet<int>& mutex_item_ids) {
    bool missing_attrs = false;

    for (const auto & attr : {"value"}) {
        if (!item_map.contains(attr)) {
            qDebug() << "Missing mandatory projectile attribute" << attr;
            missing_attrs = true;
        }
    }

    if (missing_attrs)
        return;

    QMap<QString, QString> info;
    extract_info(item_map, info);

    Projectile* projectile = new Projectile(info["name"], info["id"].toInt(), Content::get_phase(info["phase"].toInt()),
            get_projectile_type(info["type"]), item_map["value"].toDouble(), info, {}, {}, mutex_item_ids);

    items.append(projectile);

    for (const auto & handled_key : {"value"})
        item_map.remove(handled_key);
}

int ProjectileFileReader::get_projectile_type(const QString& type) {
    if (type == "ARROW")
        return ProjectileTypes::ARROW;
    if (type == "BULLET")
        return ProjectileTypes::BULLET;

    return -1;
}
