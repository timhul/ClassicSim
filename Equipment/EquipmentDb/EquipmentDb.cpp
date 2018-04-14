
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

    all_slots_items = {
        &mh_slot_items,
        &oh_slot_items,
        &ranged_items,
        &helms,
        &amulets,
        &shoulders,
        &backs,
        &chests,
        &wrists,
        &gloves,
        &belts,
        &legs,
        &boots,
        &rings,
        &trinkets
    };
}

EquipmentDb::~EquipmentDb() {
    // TODO: Check how we can avoid special handling deletion of common elements in OH/MH.
    // The issue is WeaponType::ONEHAND can be found in both lists.
    delete_items(&mh_slot_items);

    for (int i = 0; i < oh_slot_items.size(); ++i) {
        if (mh_slot_items.contains(oh_slot_items[i]))
            continue;

        delete oh_slot_items[i];
    }
    mh_slot_items.clear();
    oh_slot_items.clear();

    for (int i = 0; i < all_slots_items.size(); ++i) {
        delete_items(all_slots_items[i]);
        all_slots_items[i]->clear();
    }
}

void EquipmentDb::delete_items(QVector<Item *>* list) {
    for (int i = 0 ; i < list->size(); ++i)
        delete list->at(i);
}

void EquipmentDb::add_melee_weapon(Weapon* wpn) {
    mh_slot_items.append(wpn);
    current_patch_mh_slot_items.append(wpn);
}

Weapon* EquipmentDb::get_melee_weapon(const QString &name) {
    for (int i = 0; i < current_patch_mh_slot_items.size(); ++i) {
        if (name == current_patch_mh_slot_items[i]->get_name())
            return dynamic_cast<Weapon*>(current_patch_mh_slot_items[i]);
    }

    // TODO: How to handle caster offhands?
    for (int i = 0; i < current_patch_oh_slot_items.size(); ++i) {
        if (name == current_patch_oh_slot_items[i]->get_name())
            return dynamic_cast<Weapon*>(current_patch_oh_slot_items[i]);
    }

    return nullptr;
}

Item* EquipmentDb::get_item(const QVector<Item*> &list, const QString &name) {
    for (int i = 0; i < list.size(); ++i) {
        if (name == list[i]->get_name())
            return list[i];
    }

    return nullptr;
}

Item* EquipmentDb::get_ranged(const QString &name) {
    return get_item(current_patch_ranged_items, name);
}

Item* EquipmentDb::get_head(const QString &name) {
    return get_item(current_patch_helms, name);
}

Item* EquipmentDb::get_neck(const QString &name) {
    return get_item(current_patch_amulets, name);
}

Item* EquipmentDb::get_shoulders(const QString &name) {
    return get_item(current_patch_shoulders, name);
}

Item* EquipmentDb::get_back(const QString &name) {
    return get_item(current_patch_backs, name);
}

Item* EquipmentDb::get_chest(const QString &name) {
    return get_item(current_patch_chests, name);
}

Item* EquipmentDb::get_wrist(const QString &name) {
    return get_item(current_patch_wrists, name);
}

Item* EquipmentDb::get_gloves(const QString &name) {
    return get_item(current_patch_gloves, name);
}

Item* EquipmentDb::get_belt(const QString &name) {
    return get_item(current_patch_belts, name);
}

Item* EquipmentDb::get_legs(const QString &name) {
    return get_item(current_patch_legs, name);
}

Item* EquipmentDb::get_boots(const QString &name) {
    return get_item(current_patch_boots, name);
}

Item* EquipmentDb::get_ring(const QString &name) {
    return get_item(current_patch_rings, name);
}

Item* EquipmentDb::get_trinket(const QString &name) {
    return get_item(current_patch_trinkets, name);
}

const QVector<Item *> & EquipmentDb::get_slot_items(const int slot) const {
    switch (slot) {
    case ItemSlots::MAINHAND:
        return current_patch_mh_slot_items;
    case ItemSlots::OFFHAND:
        return current_patch_oh_slot_items;
    case ItemSlots::RANGED:
        return current_patch_ranged_items;
    case ItemSlots::HEAD:
        return current_patch_helms;
    case ItemSlots::NECK:
        return current_patch_amulets;
    case ItemSlots::SHOULDERS:
        return current_patch_shoulders;
    case ItemSlots::BACK:
        return current_patch_backs;
    case ItemSlots::CHEST:
        return current_patch_chests;
    case ItemSlots::WRIST:
        return current_patch_wrists;
    case ItemSlots::GLOVES:
        return current_patch_gloves;
    case ItemSlots::BELT:
        return current_patch_belts;
    case ItemSlots::LEGS:
        return current_patch_legs;
    case ItemSlots::BOOTS:
        return current_patch_boots;
    case ItemSlots::RING:
        return current_patch_rings;
    case ItemSlots::TRINKET:
        return current_patch_trinkets;
    }

    return current_patch_amulets;
}

void EquipmentDb::set_patch(const QString &patch) {
    this->current_patch = QVersionNumber::fromString(patch);

    set_patch_for_slot(mh_slot_items, current_patch_mh_slot_items);
    set_patch_for_slot(oh_slot_items, current_patch_oh_slot_items);
    set_patch_for_slot(ranged_items, current_patch_ranged_items);
    set_patch_for_slot(helms, current_patch_helms);
    set_patch_for_slot(amulets, current_patch_amulets);
    set_patch_for_slot(shoulders, current_patch_shoulders);
    set_patch_for_slot(backs, current_patch_backs);
    set_patch_for_slot(chests, current_patch_chests);
    set_patch_for_slot(wrists, current_patch_wrists);
    set_patch_for_slot(gloves, current_patch_gloves);
    set_patch_for_slot(belts, current_patch_belts);
    set_patch_for_slot(legs, current_patch_legs);
    set_patch_for_slot(boots, current_patch_boots);
    set_patch_for_slot(rings, current_patch_rings);
    set_patch_for_slot(trinkets, current_patch_trinkets);
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
    set_items(items, ranged_items, ItemSlots::RANGED);
    set_items(items, helms, ItemSlots::HEAD);
    set_items(items, amulets, ItemSlots::NECK);
    set_items(items, shoulders, ItemSlots::SHOULDERS);
    set_items(items, backs, ItemSlots::BACK);
    set_items(items, chests, ItemSlots::CHEST);
    set_items(items, wrists, ItemSlots::WRIST);
    set_items(items, gloves, ItemSlots::GLOVES);
    set_items(items, belts, ItemSlots::BELT);
    set_items(items, legs, ItemSlots::LEGS);
    set_items(items, boots, ItemSlots::BOOTS);
    set_items(items, rings, ItemSlots::RING);
    set_items(items, trinkets, ItemSlots::TRINKET);
}

void EquipmentDb::set_weapons(QVector<Item*> &mixed_items) {
    QSet<int> accepted_slots = {ItemSlots::MAINHAND, ItemSlots::OFFHAND};
    for (int i = 0; i < mixed_items.size(); ++i) {
        if (!accepted_slots.contains(mixed_items[i]->get_item_slot()))
            continue;

        Weapon* wpn = dynamic_cast<Weapon*>(mixed_items[i]);

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
