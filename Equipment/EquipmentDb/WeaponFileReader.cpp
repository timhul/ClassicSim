
#include "WeaponFileReader.h"
#include "Onehand.h"
#include "Mainhand.h"
#include "Offhand.h"
#include "TwoHander.h"
#include <QDebug>

void WeaponFileReader::weapon_file_handler(QXmlStreamReader &reader, QVector<Item*> &items) {
    qDebug() << "Handling weapons";
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

    for (int i = 0; i < mandatory_attrs.size(); ++i)
        add_mandatory_attr(attrs, mandatory_attrs[i], item);
}

void WeaponFileReader::create_melee_weapon(QVector<Item*> &items,
                                           QMap<QString, QString> &item_map,
                                           QVector<QPair<QString, QString>> &stats,
                                           QVector<QMap<QString, QString>>&) {
    bool missing_attrs = false;
    QVector<QString> mandatory_attrs_for_wpn = {"min", "max", "speed"};

    for (int i = 0; i < mandatory_attrs_for_wpn.size(); ++i) {
        if (!item_map.contains(mandatory_attrs_for_wpn[i])) {
            qDebug() << "Missing mandatory weapon attribute" << mandatory_attrs_for_wpn[i];
            missing_attrs = true;
        }
    }

    if (missing_attrs)
        return;

    QMap<QString, QString> info;
    extract_info(item_map, info);

    MeleeWeapon* weapon = nullptr;

    if (item_map["slot"] == "1H")
        weapon = new Onehand(item_map["name"], get_weapon_type(info["type"]),
                item_map["min"].toInt(), item_map["max"].toInt(), item_map["speed"].toFloat(), stats, info);
    else if (item_map["slot"] == "MH")
        weapon = new Mainhand(item_map["name"], get_weapon_type(info["type"]),
                item_map["min"].toInt(), item_map["max"].toInt(), item_map["speed"].toFloat(), stats, info);
    else if (item_map["slot"] == "OH")
        weapon = new Offhand(item_map["name"], get_weapon_type(info["type"]),
                item_map["min"].toInt(), item_map["max"].toInt(), item_map["speed"].toFloat(), stats, info);
    else if (item_map["slot"] == "2H")
        weapon = new TwoHander(item_map["name"], get_weapon_type(info["type"]),
                item_map["min"].toInt(), item_map["max"].toInt(), item_map["speed"].toFloat(), stats, info);

    if (weapon != nullptr)
        items.append(weapon);

    QVector<QString> handled_keys = {"name", "slot", "type", "min", "max", "speed"};

    for (int i = 0; i < handled_keys.size(); ++i) {
        item_map.remove(handled_keys[i]);
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

    return -1;
}
