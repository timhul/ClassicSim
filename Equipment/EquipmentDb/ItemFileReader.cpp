#include "ItemFileReader.h"

#include <QDebug>
#include <QDir>

#include "Item.h"
#include "ProjectileFileReader.h"
#include "WeaponFileReader.h"

ItemFileReader::ItemFileReader(EnchantInfo* enchant_info, QObject* parent) : QObject(parent), enchant_info(enchant_info) {}

void ItemFileReader::read_items(QVector<Item*>& items, const QString& path) {
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Cannot read file" << path << ":" << file.errorString();
        return;
    }

    QXmlStreamReader reader(&file);

    if (reader.readNextStartElement()) {
        if (reader.name() == "items")
            item_file_handler(reader, items);
        else if (reader.name() == "weapons")
            WeaponFileReader(enchant_info).weapon_file_handler(reader, items);
        else if (reader.name() == "projectiles")
            ProjectileFileReader(enchant_info).file_handler(reader, items);
        else
            qDebug() << QString("%1 - no appropriate handler for start element %2").arg(__func__).arg(reader.name().toString());
    }

    file.close();
}

void ItemFileReader::item_file_handler(QXmlStreamReader& reader, QVector<Item*>& items) {
    while (reader.readNextStartElement()) {
        QString classification = reader.name().toString();

        if (!reader.attributes().hasAttribute("id")) {
            qDebug() << "Missing id attribute";
            for (const auto& attr : reader.attributes())
                qDebug() << attr.name() << attr.value();
            reader.skipCurrentElement();
            continue;
        }
        if (!reader.attributes().hasAttribute("phase")) {
            qDebug() << "Missing phase attribute";
            for (const auto& attr : reader.attributes())
                qDebug() << attr.name() << attr.value();
            reader.skipCurrentElement();
            continue;
        }

        QString id = reader.attributes().value("id").toString();

        QMap<QString, QString> item_map;
        QVector<QPair<QString, QString>> stats;
        QVector<QMap<QString, QString>> procs;
        QVector<QMap<QString, QString>> uses;
        QVector<QString> spell_modifications;
        QVector<QString> special_equip_effects;
        QSet<int> mutex_item_ids;
        QVector<int> random_affixes;
        item_map["classification"] = classification;
        item_map["id"] = id;
        item_map["phase"] = reader.attributes().value("phase").toString();

        while (reader.readNextStartElement()) {
            if (reader.name() == "info") {
                info_element_reader(reader.attributes(), item_map);
                reader.skipCurrentElement();
            } else if (reader.name() == "class_restriction") {
                class_restriction_element_reader(reader.attributes(), item_map);
                reader.skipCurrentElement();
            } else if (reader.name() == "stats") {
                stats_element_reader(reader, stats);
            } else if (reader.name() == "source") {
                item_map["source"] = reader.readElementText().trimmed();
            } else if (reader.name() == "proc") {
                proc_element_reader(reader, procs);
            } else if (reader.name() == "uses") {
                use_element_reader(reader, uses);
            } else if (reader.name() == "flavour_text") {
                item_map["flavour_text"] = reader.readElementText().simplified();
            } else if (reader.name() == "special_equip_effect") {
                special_equip_effects.append(reader.readElementText().simplified());
            } else if (reader.name() == "modifies") {
                modifies_element_reader(reader, spell_modifications);
            } else if (reader.name() == "mutex") {
                mutex_element_reader(reader.attributes(), mutex_item_ids);
                reader.skipCurrentElement();
            } else if (reader.name() == "random_affixes") {
                random_affixes_element_reader(reader, random_affixes);
            } else
                reader.skipCurrentElement();
        }

        create_item(items, item_map, stats, procs, uses, spell_modifications, special_equip_effects, mutex_item_ids, random_affixes);
        item_map.remove("classification");
        warn_remaining_keys(item_map);
    }
}

void ItemFileReader::info_element_reader(const QXmlStreamAttributes& attrs, QMap<QString, QString>& item) {
    QVector<QString> mandatory_attrs = {"name", "type", "slot", "unique", "req_lvl", "item_lvl", "quality", "boe"};
    QVector<QString> optional_attrs = {"faction", "icon"};

    for (const auto& mandatory_attr : mandatory_attrs)
        add_mandatory_attr(attrs, mandatory_attr, item);

    for (const auto& optional_attr : optional_attrs)
        add_attr(attrs, optional_attr, item);
}

void ItemFileReader::class_restriction_element_reader(const QXmlStreamAttributes& attrs, QMap<QString, QString>& item) {
    item["RESTRICTED_TO_" + attrs.value("class").toString()] = "true";
}

void ItemFileReader::stats_element_reader(QXmlStreamReader& reader, QVector<QPair<QString, QString>>& stats) {
    while (reader.readNextStartElement()) {
        QXmlStreamAttributes attrs = reader.attributes();
        if (reader.name() == "stat") {
            stats.append(QPair<QString, QString>(attrs.value("type").toString(), attrs.value("value").toString()));
        }
        reader.skipCurrentElement();
    }
}

void ItemFileReader::proc_element_reader(QXmlStreamReader& reader, QVector<QMap<QString, QString>>& procs) {
    while (reader.readNextStartElement()) {
        QMap<QString, QString> map;
        QXmlStreamAttributes attrs = reader.attributes();

        if (reader.name() == "spell") {
            add_mandatory_attr(attrs, "name", map);
            add_mandatory_attr(attrs, "rate", map);
            add_mandatory_attr(attrs, "internal_cd", map);

            add_attr(attrs, "display_name", map);
            add_attr(attrs, "min", map);
            add_attr(attrs, "max", map);
            add_attr(attrs, "innate_threat", map);
            add_attr(attrs, "instant", map);
            add_attr(attrs, "duration", map);
            add_attr(attrs, "tick_rate", map);
            add_attr(attrs, "amount", map);
            add_attr(attrs, "max_stacks", map);
            add_attr(attrs, "value", map);
            add_attr(attrs, "type", map);
            add_attr(attrs, "spell_dmg_coefficient", map);
            add_attr(attrs, "proc_magic_hit", map);
            add_attr(attrs, "proc_melee_auto", map);
            add_attr(attrs, "proc_melee_skill", map);
            add_attr(attrs, "proc_melee_weapon_side", map);
            add_attr(attrs, "proc_ranged_auto", map);
            add_attr(attrs, "proc_ranged_skill", map);
        }

        if (!map.empty())
            procs.append(map);

        reader.skipCurrentElement();
    }
}

void ItemFileReader::use_element_reader(QXmlStreamReader& reader, QVector<QMap<QString, QString>>& uses) {
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

void ItemFileReader::modifies_element_reader(QXmlStreamReader& reader, QVector<QString>& spell_modifications) {
    if (!reader.attributes().hasAttribute("name")) {
        reader.skipCurrentElement();
        return;
    }

    spell_modifications.append(reader.attributes().value("name").toString());
    reader.skipCurrentElement();
}

void ItemFileReader::mutex_element_reader(const QXmlStreamAttributes& attrs, QSet<int>& mutex_item_ids) {
    if (!attrs.hasAttribute("item_id")) {
        qDebug() << "Missing item_id attribute on <mutex> element";
        return;
    }

    mutex_item_ids.insert(attrs.value("item_id").toInt());
}

void ItemFileReader::random_affixes_element_reader(QXmlStreamReader& reader, QVector<int>& random_affixes) {
    while (reader.readNextStartElement()) {
        QXmlStreamAttributes attrs = reader.attributes();
        if (reader.name() == "affix") {
            random_affixes.push_back(attrs.value("id").toInt());
        }
        reader.skipCurrentElement();
    }
}

void ItemFileReader::add_mandatory_attr(const QXmlStreamAttributes& attrs, const QString& attr, QMap<QString, QString>& item) {
    add_attr(attrs, attr, item);

    if (!item.contains(attr))
        qDebug() << "Missing" << attr << "attribute";
}

void ItemFileReader::add_attr(const QXmlStreamAttributes& attrs, const QString& attr, QMap<QString, QString>& item) {
    if (!attrs.hasAttribute(attr)) {
        return;
    }

    item[attr] = attrs.value(attr).toString();
}

void ItemFileReader::create_item(QVector<Item*>& items,
                                 QMap<QString, QString>& item_map,
                                 QVector<QPair<QString, QString>>& stats,
                                 QVector<QMap<QString, QString>>& procs,
                                 QVector<QMap<QString, QString>>& uses,
                                 QVector<QString>& spell_modifications,
                                 QVector<QString>& special_equip_effects,
                                 QSet<int>& mutex_item_ids,
                                 QVector<int>& random_affixes) {
    QVector<QString> mandatory_attrs = {"id", "phase", "name", "classification", "type", "slot", "unique", "req_lvl", "item_lvl", "quality", "boe"};

    bool missing_attrs = false;
    for (const auto& mandatory_attr : mandatory_attrs) {
        if (!item_map.contains(mandatory_attr)) {
            qDebug() << "Missing mandatory base attribute" << mandatory_attr;
            missing_attrs = true;
        }
    }

    if (missing_attrs)
        return;

    QMap<QString, QString> info;
    extract_info(item_map, info);

    items.append(new Item(info["name"], info["id"].toInt(), Content::get_phase(info["phase"].toInt()), enchant_info, info, stats, procs, uses,
                          spell_modifications, special_equip_effects, mutex_item_ids, random_affixes));
}

void ItemFileReader::extract_info(QMap<QString, QString>& item, QMap<QString, QString>& info) {
    QVector<QString> keys = {"id",
                             "name",
                             "phase",
                             "type",
                             "slot",
                             "boe",
                             "item_lvl",
                             "req_lvl",
                             "faction",
                             "unique",
                             "quality",
                             "source",
                             "icon",
                             "RESTRICTED_TO_WARRIOR",
                             "RESTRICTED_TO_PALADIN",
                             "RESTRICTED_TO_HUNTER",
                             "RESTRICTED_TO_ROGUE",
                             "RESTRICTED_TO_SHAMAN",
                             "RESTRICTED_TO_DRUID",
                             "RESTRICTED_TO_MAGE",
                             "RESTRICTED_TO_PRIEST",
                             "RESTRICTED_TO_WARLOCK",
                             "flavour_text"};

    extract(keys, item, info);
}

void ItemFileReader::extract(QVector<QString> handled_keys, QMap<QString, QString>& source, QMap<QString, QString>& target) {
    for (const auto& key : handled_keys) {
        if (source.contains(key)) {
            target[key] = source.take(key);
        }
    }
}

void ItemFileReader::warn_remaining_keys(QMap<QString, QString>& item) {
    QMap<QString, QString>::const_iterator it = item.constBegin();
    auto end = item.constEnd();
    while (it != end) {
        qDebug() << "Warning: Unhandled key" << QString("%1: %2").arg(it.key(), it.value());
        ++it;
    }
}
