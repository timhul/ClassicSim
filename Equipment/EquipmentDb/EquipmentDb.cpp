
#include "EquipmentDb.h"
#include "ItemFileReader.h"
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
    for (int i = 0; i < mh_slot_items.size(); ++i) {
        delete mh_slot_items[i];
    }
}

void EquipmentDb::add_melee_weapon(MeleeWeapon* wpn) {
    mh_slot_items.append(wpn);
    current_patch_mh_slot_items.append(wpn);
}

MeleeWeapon* EquipmentDb::get_melee_weapon(const QString &name) {
    for (int i = 0; i < current_patch_mh_slot_items.size(); ++i) {
        if (name == current_patch_mh_slot_items[i]->get_name())
            return dynamic_cast<MeleeWeapon*>(current_patch_mh_slot_items[i]);
    }

    // TODO: How to handle caster offhands?
    for (int i = 0; i < current_patch_oh_slot_items.size(); ++i) {
        if (name == current_patch_oh_slot_items[i]->get_name())
            return dynamic_cast<MeleeWeapon*>(current_patch_oh_slot_items[i]);
    }

    return nullptr;
}

Item* EquipmentDb::get_helm(const QString &name) {
    for (int i = 0; i < current_patch_helms.size(); ++i) {
        if (name == current_patch_helms[i]->get_name())
            return current_patch_helms[i];
    }

    return nullptr;
}

const QVector<Item *>& EquipmentDb::get_mh_slot_items() const {
    return current_patch_mh_slot_items;
}

void EquipmentDb::set_patch(const QString &patch) {
    this->current_patch = QVersionNumber::fromString(patch);

    set_patch_for_slot(mh_slot_items, current_patch_mh_slot_items);
    set_patch_for_slot(oh_slot_items, current_patch_oh_slot_items);
    set_patch_for_slot(helms, current_patch_helms);
}

void EquipmentDb::set_patch_for_slot(QVector<Item *> &total_slot_items, QVector<Item*> &patch_slot_items) {
    patch_slot_items.clear();
    QMap<QString, Item*> tmp_names;

    for (int i = 0; i < total_slot_items.size(); ++i) {
        if (item_valid_for_current_patch(total_slot_items[i]->get_value("patch"))) {
            if (tmp_names.contains(total_slot_items[i]->get_name())) {
                QString curr_tmp_patch = tmp_names[total_slot_items[i]->get_name()]->get_value("patch");
                QString contender_patch = total_slot_items[i]->get_value("patch");

                if (QVersionNumber::fromString(contender_patch) < QVersionNumber::fromString(curr_tmp_patch))
                    continue;
            }
            tmp_names[total_slot_items[i]->get_name()] = total_slot_items[i];
        }
    }

    for (auto it: tmp_names.keys())
        patch_slot_items.append(tmp_names.value(it));
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

    QVector<Item*> items;

    for (int i = 0; i < equipment_file_paths.size(); ++i) {
        ItemFileReader().read_items(items, equipment_file_paths[i]);
    }

    set_weapons(items);
    set_items(items, helms, ItemSlots::HEAD);
}

void EquipmentDb::set_weapons(QVector<Item*> &mixed_items) {
    QSet<int> accepted_slots = {ItemSlots::MAINHAND, ItemSlots::OFFHAND};
    for (int i = 0; i < mixed_items.size(); ++i) {
        if (!accepted_slots.contains(mixed_items[i]->get_item_slot()))
            continue;

        MeleeWeapon* wpn = dynamic_cast<MeleeWeapon*>(mixed_items[i]);

        switch (wpn->get_weapon_slot()) {
        case WeaponSlots::MAINHAND:
        case WeaponSlots::TWOHAND:
            mh_slot_items.append(mixed_items.takeAt(i));
            --i;
            break;
        case WeaponSlots::ONEHAND:
            mh_slot_items.append(mixed_items.at(i));
        case WeaponSlots::OFFHAND:
            oh_slot_items.append(mixed_items.takeAt(i));
            --i;
            break;
        }
    }
}

void EquipmentDb::set_items(QVector<Item*> &mixed_items, QVector<Item*> &sorted, const int slot) {
    for (int i = 0; i < mixed_items.size(); ++i) {
        if (mixed_items[i]->get_item_slot() == slot) {
            sorted.append(mixed_items.takeAt(i));
            --i;
        }
    }
}
