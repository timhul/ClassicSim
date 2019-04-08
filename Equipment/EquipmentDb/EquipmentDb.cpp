#include "EquipmentDb.h"

#include <QDebug>
#include <QDir>
#include <QVersionNumber>

#include "ItemFileReader.h"
#include "Projectile.h"
#include "Utils/Check.h"
#include "Weapon.h"

EquipmentDb::EquipmentDb(QObject* parent):
    QObject(parent)
{
    read_equipment_files();
    set_patch(QVersionNumber::fromString("1.12.1"));

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
        &trinkets,
        &projectiles
    };
}

EquipmentDb::~EquipmentDb() {
    delete_items(&mh_slot_items);
    delete_items(&oh_slot_items);

    mh_slot_items.clear();
    oh_slot_items.clear();

    for (auto & all_slots_item : all_slots_items) {
        delete_items(all_slots_item);
        all_slots_item->clear();
    }
}

void EquipmentDb::delete_items(QVector<Item *>* list) {
    for (auto i : *list)
        delete i;
}

void EquipmentDb::add_item_id(Item* item) {
    item_id_to_item[item->get_item_id()] = item;
}

void EquipmentDb::add_melee_weapon(Weapon* wpn) {
    add_item_id(wpn);
    mh_slot_items.append(wpn);
    current_patch_mh_slot_items.append(wpn);
}

void EquipmentDb::add_ranged(Weapon* wpn) {
    add_item_id(wpn);
    ranged_items.append(wpn);
    current_patch_ranged_items.append(wpn);
}

void EquipmentDb::add_ring(Item* ring) {
    add_item_id(ring);
    rings.append(ring);
    current_patch_rings.append(ring);
}

Weapon* EquipmentDb::get_melee_weapon(const int item_id) const {
    for (auto & current_patch_mh_slot_item : current_patch_mh_slot_items) {
        if (item_id == current_patch_mh_slot_item->get_item_id())
            return new Weapon(dynamic_cast<Weapon*>(current_patch_mh_slot_item));
    }

    // CSIM-74: How to handle caster offhands?
    for (auto & current_patch_oh_slot_item : current_patch_oh_slot_items) {
        if (item_id == current_patch_oh_slot_item->get_item_id())
            return new Weapon(dynamic_cast<Weapon*>(current_patch_oh_slot_item));
    }

    return nullptr;
}

Item* EquipmentDb::get_item(const QVector<Item*> &item_list, const int item_id) const {
    for (auto item : item_list) {
        if (item_id == item->get_item_id())
            return new Item(item);
    }

    return nullptr;
}

Weapon *EquipmentDb::get_ranged(const int item_id) const {
    for (auto & current_patch_ranged_slot_item : current_patch_ranged_items) {
        if (item_id == current_patch_ranged_slot_item->get_item_id())
            return new Weapon(dynamic_cast<Weapon*>(current_patch_ranged_slot_item));
    }

    return nullptr;
}

Item* EquipmentDb::get_head(const int item_id) const {
    return get_item(current_patch_helms, item_id);
}

Item* EquipmentDb::get_neck(const int item_id) const {
    return get_item(current_patch_amulets, item_id);
}

Item* EquipmentDb::get_shoulders(const int item_id) const {
    return get_item(current_patch_shoulders, item_id);
}

Item* EquipmentDb::get_back(const int item_id) const {
    return get_item(current_patch_backs, item_id);
}

Item* EquipmentDb::get_chest(const int item_id) const {
    return get_item(current_patch_chests, item_id);
}

Item* EquipmentDb::get_wrist(const int item_id) const {
    return get_item(current_patch_wrists, item_id);
}

Item* EquipmentDb::get_gloves(const int item_id) const {
    return get_item(current_patch_gloves, item_id);
}

Item* EquipmentDb::get_belt(const int item_id) const {
    return get_item(current_patch_belts, item_id);
}

Item* EquipmentDb::get_legs(const int item_id) const {
    return get_item(current_patch_legs, item_id);
}

Item* EquipmentDb::get_boots(const int item_id) const {
    return get_item(current_patch_boots, item_id);
}

Item* EquipmentDb::get_ring(const int item_id) const {
    return get_item(current_patch_rings, item_id);
}

Item* EquipmentDb::get_trinket(const int item_id) const {
    return get_item(current_patch_trinkets, item_id);
}

Item* EquipmentDb::get_caster_offhand(const int) const {
    // CSIM-74: Get caster offhand.
    return nullptr;
}

Item* EquipmentDb::get_relic(const int) const {
    // CSIM-74: Get relic.
    return nullptr;
}

Projectile* EquipmentDb::get_projectile(const int item_id) const {
    for (auto & current_patch_projectile : current_patch_projectiles) {
        if (item_id == current_patch_projectile->get_item_id())
            return new Projectile(dynamic_cast<Projectile*>(current_patch_projectile));
    }

    return nullptr;
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
    case ItemSlots::PROJECTILE:
        return current_patch_projectiles;
    }

    return current_patch_amulets;
}

QString EquipmentDb::get_name_for_item_id(const int item_id) const {
    check((item_id_to_item.contains(item_id)), QString("Unknown item id '%1'").arg(item_id).toStdString());

    return item_id_to_item[item_id]->get_name();
}

void EquipmentDb::set_patch(const QVersionNumber& patch) {
    this->current_patch = patch;

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
    set_patch_for_slot(projectiles, current_patch_projectiles);
}

void EquipmentDb::set_patch_for_slot(QVector<Item*> &total_slot_items, QVector<Item*> &patch_slot_items) {
    patch_slot_items.clear();
    QMap<int, Item*> tmp_items;

    for (auto & item : total_slot_items) {
        if (item_valid_for_current_patch(item->get_value("patch"))) {
            if (tmp_items.contains(item->get_item_id())) {
                QString curr_tmp_patch = tmp_items[item->get_item_id()]->get_value("patch");
                QString contender_patch = item->get_value("patch");

                if (QVersionNumber::fromString(contender_patch) < QVersionNumber::fromString(curr_tmp_patch))
                    continue;
            }
            tmp_items[item->get_item_id()] = item;
        }
    }

    for (auto & item : tmp_items)
        patch_slot_items.append(item);
}

bool EquipmentDb::item_valid_for_current_patch(const QString &item_patch) const {
    return current_patch >= QVersionNumber::fromString(item_patch);
}

void EquipmentDb::read_equipment_files() {
    QFile file("equipment_paths.xml");

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Cannot read file:" << file.errorString();
        qDebug() << QDir::currentPath();
        exit(0);
    }

    QXmlStreamReader reader(&file);
    QVector<QString> equipment_file_paths;

    if (reader.readNextStartElement()) {
        if (reader.name() != "paths") {
            qDebug() << "Expected <paths> root element in equipment_paths.xml.";
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
        qDebug() << "Failed to read equipment_paths.xml.";

    file.close();

    if (equipment_file_paths.empty())
        qDebug() << "Failed to find equipment files in equipment_paths.xml";

    QVector<Item*> items;

    for (const auto & equipment_file_path : equipment_file_paths) {
        ItemFileReader().read_items(items, equipment_file_path);
    }

    take_weapons_from_given_items(items);
    take_items_of_slot_from_given_items(items, helms, ItemSlots::HEAD);
    take_items_of_slot_from_given_items(items, amulets, ItemSlots::NECK);
    take_items_of_slot_from_given_items(items, shoulders, ItemSlots::SHOULDERS);
    take_items_of_slot_from_given_items(items, backs, ItemSlots::BACK);
    take_items_of_slot_from_given_items(items, chests, ItemSlots::CHEST);
    take_items_of_slot_from_given_items(items, wrists, ItemSlots::WRIST);
    take_items_of_slot_from_given_items(items, gloves, ItemSlots::GLOVES);
    take_items_of_slot_from_given_items(items, belts, ItemSlots::BELT);
    take_items_of_slot_from_given_items(items, legs, ItemSlots::LEGS);
    take_items_of_slot_from_given_items(items, boots, ItemSlots::BOOTS);
    take_items_of_slot_from_given_items(items, rings, ItemSlots::RING);
    take_items_of_slot_from_given_items(items, trinkets, ItemSlots::TRINKET);
    take_items_of_slot_from_given_items(items, projectiles, ItemSlots::PROJECTILE);

    for (auto & item : items) {
        qDebug() << "Failed to classify slot for" << item->get_name();
        delete item;
    }
}

void EquipmentDb::take_weapons_from_given_items(QVector<Item*> &mixed_items) {
    Item* item = nullptr;
    for (int i = 0; i < mixed_items.size(); ++i) {
        switch (mixed_items[i]->get_weapon_slot()) {
        case WeaponSlots::NON_WEAPON:
            break;
        case WeaponSlots::MAINHAND:
        case WeaponSlots::TWOHAND:
            item = mixed_items.takeAt(i);
            mh_slot_items.append(item);
            add_item_id(item);
            --i;
            break;
        case WeaponSlots::ONEHAND:
            mh_slot_items.append(mixed_items.at(i));
            // C++17 [[clang::fallthrough]];
        case WeaponSlots::OFFHAND:
            item = mixed_items.takeAt(i);
            oh_slot_items.append(new Weapon(dynamic_cast<Weapon*>(item)));
            add_item_id(item);
            --i;
            break;
        case WeaponSlots::RANGED:
            item = mixed_items.takeAt(i);
            ranged_items.append(new Weapon(dynamic_cast<Weapon*>(item)));
            add_item_id(item);
            --i;
            break;
        }
    }
}

void EquipmentDb::take_items_of_slot_from_given_items(QVector<Item*> &mixed_items, QVector<Item*> &sorted, const int slot) {
    Item* item = nullptr;
    for (int i = 0; i < mixed_items.size(); ++i) {
        if (mixed_items[i]->get_item_slot() == slot) {
            item = mixed_items.takeAt(i);
            add_item_id(item);
            sorted.append(item);
            --i;
        }
    }
}
