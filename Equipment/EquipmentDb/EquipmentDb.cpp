
#include "EquipmentDb.h"
#include <QDebug>
#include <QDir>

#include "Onehand.h"
#include "Mainhand.h"
#include "Offhand.h"
#include "TwoHander.h"


EquipmentDb::EquipmentDb(QObject* parent):
    QObject(parent)
{
    read_equipment_files();
    set_patch("1.12.1");
}

EquipmentDb::~EquipmentDb() {
    for (int i = 0; i < melee_weapons.size(); ++i) {
        delete melee_weapons[i];
    }
}

MeleeWeapon* EquipmentDb::get_melee_weapon(const QString &name) {
    for (int i = 0; i < current_patch_melee_weapons.size(); ++i) {
        if (name == current_patch_melee_weapons[i]->get_name())
            return current_patch_melee_weapons[i];
    }

    return nullptr;
}

void EquipmentDb::set_patch(const QString &patch) {
    this->current_patch = QVersionNumber::fromString(patch);

    current_patch_melee_weapons.clear();
    QMap<QString, MeleeWeapon*> tmp_names;

    for (int i = 0; i < melee_weapons.size(); ++i) {
        if (item_valid_for_current_patch(melee_weapons[i]->get_patch())) {
            if (tmp_names.contains(melee_weapons[i]->get_name())) {
                QString curr_tmp_patch = tmp_names[melee_weapons[i]->get_name()]->get_patch();
                QString contender_patch = melee_weapons[i]->get_patch();

                if (QVersionNumber::fromString(contender_patch) < QVersionNumber::fromString(curr_tmp_patch))
                    continue;
            }
            tmp_names[melee_weapons[i]->get_name()] = melee_weapons[i];
        }
    }

    for (auto it: tmp_names.keys())
        current_patch_melee_weapons.append(tmp_names.value(it));

    for (int i = 0; i < current_patch_melee_weapons.size(); ++i) {
        qDebug() << current_patch_melee_weapons[i]->get_name() << current_patch_melee_weapons[i]->get_patch();
    }
}

bool EquipmentDb::item_valid_for_current_patch(const QString &item_patch) {
    return current_patch >= QVersionNumber::fromString(item_patch);
}

void EquipmentDb::read_equipment_files() {
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
        if (reader.name() == "melee_weapon" || reader.name() == "ranged_weapon") {
            QString classification = reader.name().toString();

            if (!reader.attributes().hasAttribute("name")) {
                qDebug() << "Missing name attribute on weapon element";
                reader.skipCurrentElement();
                continue;
            }
            QString name = reader.attributes().value("name").toString();

            qDebug() << "Processing" << classification << name;

            while (reader.readNextStartElement()) {
                if (reader.name() != "patch") {
                    qDebug() << "Skipping element" << reader.name();
                    reader.skipCurrentElement();
                    continue;
                }
                QMap<QString, QString> item;
                QVector<QPair<QString, QString>> stats;
                QVector<QMap<QString, QString>> procs;
                item["classification"] = classification;
                item["name"] = name;
                item["patch"] = reader.attributes().value("name").toString();

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
                        stats_element_reader(reader, stats);
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

                create_item(item, stats, procs);
                item.remove("classification");
                warn_remaining_keys(item);
            }
        }
        else {
            qDebug() << "Skipping element" << reader.name();
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

void EquipmentDb::stats_element_reader(QXmlStreamReader &reader, QVector<QPair<QString, QString>> &stats) {
    while (reader.readNextStartElement()) {
        QXmlStreamAttributes attrs = reader.attributes();
        if (reader.name() == "stat") {
            stats.append(QPair<QString, QString>(attrs.value("type").toString(), attrs.value("value").toString()));
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

void EquipmentDb::create_item(QMap<QString, QString> &item, QVector<QPair<QString, QString>> &stats, QVector<QMap<QString, QString>> &procs) {
    QVector<QString> mandatory_attrs = {"name", "classification", "patch", "type", "slot",
                                        "unique", "req_lvl", "item_lvl", "quality", "boe"};

    bool missing_attrs = false;
    for (int i = 0; i < mandatory_attrs.size(); ++i) {
        if (!item.contains(mandatory_attrs[i])) {
            qDebug() << "Missing mandatory base attribute" << mandatory_attrs[i];
            missing_attrs = true;
        }
    }

    if (missing_attrs)
        return;

    if (item["classification"] == "melee_weapon")
        create_melee_weapon(item, stats, procs);
    else if (item["classification"] == "ranged_weapon")
        create_ranged_weapon(item, stats, procs);

}

void EquipmentDb::create_melee_weapon(QMap<QString, QString> &item, QVector<QPair<QString, QString>> &stats, QVector<QMap<QString, QString>>&) {
    bool missing_attrs = false;
    QVector<QString> mandatory_attrs_for_wpn = {"min", "max", "speed"};

    for (int i = 0; i < mandatory_attrs_for_wpn.size(); ++i) {
        if (!item.contains(mandatory_attrs_for_wpn[i])) {
            qDebug() << "Missing mandatory weapon attribute" << mandatory_attrs_for_wpn[i];
            missing_attrs = true;
        }
    }

    if (missing_attrs)
        return;

    QMap<QString, QString> info;
    extract_info(item, info);

    MeleeWeapon* weapon;

    if (item["slot"] == "1H")
        weapon = new Onehand(item["name"], get_weapon_type(item["type"]),
                item["min"].toInt(), item["max"].toInt(), item["speed"].toFloat(), stats, info);
    else if (item["slot"] == "MH")
        weapon = new Mainhand(item["name"], get_weapon_type(item["type"]),
                item["min"].toInt(), item["max"].toInt(), item["speed"].toFloat(), stats, info);
    else if (item["slot"] == "OH")
        weapon = new Offhand(item["name"], get_weapon_type(item["type"]),
                item["min"].toInt(), item["max"].toInt(), item["speed"].toFloat(), stats, info);
    else if (item["slot"] == "2H")
        weapon = new TwoHander(item["name"], get_weapon_type(item["type"]),
                item["min"].toInt(), item["max"].toInt(), item["speed"].toFloat(), stats, info);

    melee_weapons.append(weapon);

    QVector<QString> handled_keys = {"name", "slot", "type", "min", "max", "speed"};

    for (int i = 0; i < handled_keys.size(); ++i) {
        item.remove(handled_keys[i]);
    }
}

void EquipmentDb::create_ranged_weapon(QMap<QString, QString> &, QVector<QPair<QString, QString>> &, QVector<QMap<QString, QString>> &) {

}

void EquipmentDb::extract_info(QMap<QString, QString> &item, QMap<QString, QString> &info) {
    QVector<QString> keys = {"patch", "boe", "item_lvl", "req_lvl", "faction", "unique", "quality", "source",
                            "RESTRICTED_TO_WARRIOR", "RESTRICTED_TO_PALADIN", "RESTRICTED_TO_HUNTER",
                            "RESTRICTED_TO_ROGUE"};

    extract(keys, item, info);
}

void EquipmentDb::extract(QVector<QString> handled_keys, QMap<QString, QString> &source, QMap<QString, QString> &target) {
    for (int i = 0; i < handled_keys.size(); ++i) {
        QString key = handled_keys[i];
        if (source.contains(key)) {
            target[key] = source.take(key);
        }
    }
}

void EquipmentDb::warn_remaining_keys(QMap<QString, QString> &item) {
    for (auto it : item.keys()) {
        qDebug() << "Warning: Unhandled key" << it;
    }
}

int EquipmentDb::get_weapon_type(const QString &type) {
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
