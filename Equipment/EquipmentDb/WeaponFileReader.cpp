
#include "WeaponFileReader.h"
#include "Onehand.h"
#include "Mainhand.h"
#include "Offhand.h"
#include "TwoHander.h"
#include "Ranged.h"
#include <QDebug>

void WeaponFileReader::weapon_file_handler(QXmlStreamReader &reader, QVector<Item*> &items) {
    while (reader.readNextStartElement()) {
        if (reader.name() == "melee_weapon" || reader.name() == "ranged_weapon") {
            QString classification = reader.name().toString();

            if (!reader.attributes().hasAttribute("name")) {
                qDebug() << "Missing name attribute on weapon element";
                reader.skipCurrentElement();
                continue;
            }
            QString name = reader.attributes().value("name").toString();

            while (reader.readNextStartElement()) {
                if (reader.name() != "patch") {
                    qDebug() << "Skipping element" << reader.name();
                    reader.skipCurrentElement();
                    continue;
                }
                QMap<QString, QString> item_map;
                QVector<QPair<QString, QString>> stats;
                QVector<QMap<QString, QString>> procs;
                item_map["classification"] = classification;
                item_map["name"] = name;
                item_map["patch"] = reader.attributes().value("name").toString();

                while (reader.readNextStartElement()) {
                    if (reader.name() == "info") {
                        info_element_reader(reader.attributes(), item_map);
                        reader.skipCurrentElement();
                    }
                    else if (reader.name() == "dmg_range") {
                        dmg_range_element_reader(reader.attributes(), item_map);
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
                    else if (reader.name() == "flavour_text") {
                        item_map["flavour_text"] = reader.readElementText().simplified();
                    }
                    else if (reader.name() == "special_equip_effect") {
                        item_map["special_equip_effect"] = reader.readElementText().simplified();
                    }
                    else
                        reader.skipCurrentElement();
                }

                create_melee_weapon(items, item_map, stats, procs);
                item_map.remove("classification");
                warn_remaining_keys(item_map);
            }
        }
        else {
            qDebug() << "Skipping element" << reader.name();
            reader.skipCurrentElement();
        }
    }
}

void WeaponFileReader::dmg_range_element_reader(const QXmlStreamAttributes &attrs, QMap<QString, QString> &item) {
    QVector<QString> mandatory_attrs = {"min", "max", "speed"};

    for (const auto & mandatory_attr : mandatory_attrs)
        add_mandatory_attr(attrs, mandatory_attr, item);
}

void WeaponFileReader::create_melee_weapon(QVector<Item*> &items,
                                           QMap<QString, QString> &item_map,
                                           QVector<QPair<QString, QString>> &stats,
                                           QVector<QMap<QString, QString>>& procs) {
    bool missing_attrs = false;
    QVector<QString> mandatory_attrs_for_wpn = {"min", "max", "speed"};

    for (const auto & i : mandatory_attrs_for_wpn) {
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
        weapon = new Onehand(item_map["name"], get_weapon_type(info["type"]),
                item_map["min"].toUInt(), item_map["max"].toUInt(), item_map["speed"].toDouble(), stats, info, procs);
    else if (info["slot"] == "MH")
        weapon = new Mainhand(item_map["name"], get_weapon_type(info["type"]),
                item_map["min"].toUInt(), item_map["max"].toUInt(), item_map["speed"].toDouble(), stats, info, procs);
    else if (info["slot"] == "OH")
        weapon = new Offhand(item_map["name"], get_weapon_type(info["type"]),
                item_map["min"].toUInt(), item_map["max"].toUInt(), item_map["speed"].toDouble(), stats, info, procs);
    else if (info["slot"] == "2H")
        weapon = new TwoHander(item_map["name"], get_weapon_type(info["type"]),
                item_map["min"].toUInt(), item_map["max"].toUInt(), item_map["speed"].toDouble(), stats, info, procs);
    else if (info["slot"] == "RANGED")
        weapon = new Ranged(item_map["name"], get_weapon_type(info["type"]),
                item_map["min"].toUInt(), item_map["max"].toUInt(), item_map["speed"].toDouble(), stats, info, procs);

    if (weapon != nullptr)
        items.append(weapon);

    QVector<QString> handled_keys = {"name", "type", "min", "max", "speed"};

    for (const auto & handled_key : handled_keys) {
        item_map.remove(handled_key);
    }
}

void WeaponFileReader::create_ranged_weapon(QVector<Item*> &, QMap<QString, QString> &, QVector<QPair<QString, QString>> &, QVector<QMap<QString, QString>> &) {

}

int WeaponFileReader::get_weapon_type(const QString &type) {
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

    return -1;
}
