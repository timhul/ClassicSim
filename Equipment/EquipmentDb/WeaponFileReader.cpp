#include "WeaponFileReader.h"

#include <QDebug>

#include "Weapon.h"

void WeaponFileReader::weapon_file_handler(QXmlStreamReader& reader, QVector<Item*>& items) {
    while (reader.readNextStartElement()) {
        if (reader.name() == "melee_weapon" || reader.name() == "ranged_weapon") {
            QString classification = reader.name().toString();

            if (!reader.attributes().hasAttribute("id")) {
                qDebug() << "Missing id attribute on weapon element";
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
                } else if (reader.name() == "dmg_range") {
                    dmg_range_element_reader(reader.attributes(), item_map);
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
                } else if (reader.name() == "mutex") {
                    mutex_element_reader(reader.attributes(), mutex_item_ids);
                    reader.skipCurrentElement();
                } else if (reader.name() == "random_affixes") {
                    random_affixes_element_reader(reader, random_affixes);
                } else
                    reader.skipCurrentElement();
            }

            create_weapon(items, item_map, stats, procs, uses, special_equip_effects, mutex_item_ids, random_affixes);
            item_map.remove("classification");
            warn_remaining_keys(item_map);
        } else {
            qDebug() << "Skipping element" << reader.name();
            reader.skipCurrentElement();
        }
    }
}

void WeaponFileReader::dmg_range_element_reader(const QXmlStreamAttributes& attrs, QMap<QString, QString>& item) {
    QVector<QString> mandatory_attrs = {"min", "max", "speed"};

    for (const auto& mandatory_attr : mandatory_attrs)
        add_mandatory_attr(attrs, mandatory_attr, item);
}

void WeaponFileReader::create_weapon(QVector<Item*>& items,
                                     QMap<QString, QString>& item_map,
                                     QVector<QPair<QString, QString>>& stats,
                                     QVector<QMap<QString, QString>>& procs,
                                     QVector<QMap<QString, QString>>& uses,
                                     QVector<QString>& special_equip_effects,
                                     QSet<int>& mutex_item_ids,
                                     QVector<int>& random_affixes) {
    bool missing_attrs = false;
    QVector<QString> mandatory_attrs_for_wpn = {"min", "max", "speed"};

    for (const auto& i : mandatory_attrs_for_wpn) {
        if (!item_map.contains(i)) {
            qDebug() << "Missing mandatory weapon attribute" << i;
            missing_attrs = true;
        }
    }

    if (missing_attrs)
        return;

    QMap<QString, QString> info;
    extract_info(item_map, info);

    Weapon* weapon = nullptr;

    if (info["slot"] == "1H")
        weapon = new Weapon(info["name"], info["id"].toInt(), Content::get_phase(info["phase"].toInt()), get_weapon_type(info["type"]),
                            WeaponSlots::ONEHAND, item_map["min"].toUInt(), item_map["max"].toUInt(), item_map["speed"].toDouble(), enchant_info,
                            info, stats, procs, uses, special_equip_effects, mutex_item_ids, random_affixes);
    else if (info["slot"] == "MH")
        weapon = new Weapon(info["name"], info["id"].toInt(), Content::get_phase(info["phase"].toInt()), get_weapon_type(info["type"]),
                            WeaponSlots::MAINHAND, item_map["min"].toUInt(), item_map["max"].toUInt(), item_map["speed"].toDouble(), enchant_info,
                            info, stats, procs, uses, special_equip_effects, mutex_item_ids, random_affixes);
    else if (info["slot"] == "OH")
        weapon = new Weapon(info["name"], info["id"].toInt(), Content::get_phase(info["phase"].toInt()), get_weapon_type(info["type"]),
                            WeaponSlots::OFFHAND, item_map["min"].toUInt(), item_map["max"].toUInt(), item_map["speed"].toDouble(), enchant_info,
                            info, stats, procs, uses, special_equip_effects, mutex_item_ids, random_affixes);
    else if (info["slot"] == "2H")
        weapon = new Weapon(info["name"], info["id"].toInt(), Content::get_phase(info["phase"].toInt()), get_weapon_type(info["type"]),
                            WeaponSlots::TWOHAND, item_map["min"].toUInt(), item_map["max"].toUInt(), item_map["speed"].toDouble(), enchant_info,
                            info, stats, procs, uses, special_equip_effects, mutex_item_ids, random_affixes);
    else if (info["slot"] == "RANGED")
        weapon = new Weapon(info["name"], info["id"].toInt(), Content::get_phase(info["phase"].toInt()), get_weapon_type(info["type"]),
                            WeaponSlots::RANGED, item_map["min"].toUInt(), item_map["max"].toUInt(), item_map["speed"].toDouble(), enchant_info, info,
                            stats, procs, uses, special_equip_effects, mutex_item_ids, random_affixes);

    if (weapon != nullptr)
        items.append(weapon);

    QVector<QString> handled_keys = {"id", "phase", "type", "min", "max", "speed"};

    for (const auto& handled_key : handled_keys) {
        item_map.remove(handled_key);
    }
}

int WeaponFileReader::get_weapon_type(const QString& type) {
    if (type == "AXE")
        return WeaponTypes::AXE;
    if (type == "DAGGER")
        return WeaponTypes::DAGGER;
    if (type == "FIST")
        return WeaponTypes::FIST;
    if (type == "MACE")
        return WeaponTypes::MACE;
    if (type == "POLEARM")
        return WeaponTypes::POLEARM;
    if (type == "STAFF")
        return WeaponTypes::STAFF;
    if (type == "SWORD")
        return WeaponTypes::SWORD;
    if (type == "BOW")
        return WeaponTypes::BOW;
    if (type == "CROSSBOW")
        return WeaponTypes::CROSSBOW;
    if (type == "GUN")
        return WeaponTypes::GUN;
    if (type == "THROWN")
        return WeaponTypes::THROWN;
    if (type == "WAND")
        return WeaponTypes::WAND;
    if (type == "TWOHAND_AXE")
        return WeaponTypes::TWOHAND_AXE;
    if (type == "TWOHAND_MACE")
        return WeaponTypes::TWOHAND_MACE;
    if (type == "TWOHAND_SWORD")
        return WeaponTypes::TWOHAND_SWORD;
    if (type == "CASTER_OFFHAND")
        return WeaponTypes::CASTER_OFFHAND;
    if (type == "SHIELD")
        return WeaponTypes::SHIELD;

    return -1;
}
