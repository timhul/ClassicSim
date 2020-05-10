#include "EquipmentDb.h"

#include <cmath>

#include <QDebug>
#include <QDir>
#include <QVersionNumber>

#include "ItemFileReader.h"
#include "Projectile.h"
#include "Quiver.h"
#include "Utils/Check.h"
#include "Weapon.h"

EquipmentDb::EquipmentDb(QObject* parent) : QObject(parent), enchant_info(new EnchantInfo()) {
    read_equipment_files();
    add_druid_cat_form_claws();
    add_druid_bear_form_paws();
    set_content_phase(Content::Phase::Naxxramas);

    all_slots_items = {&mh_slot_items, &oh_slot_items, &ranged_items, &helms, &amulets,  &shoulders,   &backs,  &chests,  &wrists, &gloves,
                       &belts,         &legs,          &boots,        &rings, &trinkets, &projectiles, &relics, &quivers, &shields};
}

EquipmentDb::~EquipmentDb() {
    delete_items(&mh_slot_items);
    delete_items(&oh_slot_items);

    mh_slot_items.clear();
    oh_slot_items.clear();

    for (const auto& all_slots_item : all_slots_items) {
        delete_items(all_slots_item);
        all_slots_item->clear();
    }

    delete enchant_info;
}

void EquipmentDb::delete_items(QVector<Item*>* list) {
    for (const auto i : *list)
        delete i;
}

void EquipmentDb::add_item_id(Item* item) {
    if (item_id_to_item.contains(item->item_id))
        qDebug() << "Warning:" << item->name << "overwrites" << item_id_to_item[item->item_id]->name;

    item_id_to_item[item->item_id] = item;
}

void EquipmentDb::add_druid_cat_form_claws() {
    for (int i = 1; i <= 60; ++i) {
        const unsigned min_dmg = static_cast<unsigned>(std::max(1, static_cast<int>(std::round(i * 0.85))));
        const unsigned max_dmg = static_cast<unsigned>(std::max(1, static_cast<int>(std::round(i * 1.25))));
        const int item_id = 11223300 + i;
        Weapon* claw = new Weapon(QString("Claw level %1").arg(i), item_id, Content::Phase::MoltenCore, WeaponTypes::FIST, WeaponSlots::MAINHAND,
                                  min_dmg, max_dmg, 1.0, enchant_info);
        add_melee_weapon(claw);
    }
}

void EquipmentDb::add_druid_bear_form_paws() {
    for (int i = 1; i <= 60; ++i) {
        const unsigned min_dmg = static_cast<unsigned>(std::max(1, static_cast<int>(std::round(2.5 * i * 0.85))));
        const unsigned max_dmg = static_cast<unsigned>(std::max(1, static_cast<int>(std::round(2.5 * i * 1.25))));
        const int item_id = 11223400 + i;
        Weapon* paws = new Weapon(QString("Paws level %1").arg(i), item_id, Content::Phase::MoltenCore, WeaponTypes::FIST, WeaponSlots::MAINHAND,
                                  min_dmg, max_dmg, 2.5, enchant_info);
        add_melee_weapon(paws);
    }
}

void EquipmentDb::add_melee_weapon(Weapon* wpn) {
    add_item_id(wpn);
    mh_slot_items.append(wpn);
    current_phase_mh_slot_items.append(wpn);
}

void EquipmentDb::add_ranged(Weapon* wpn) {
    add_item_id(wpn);
    ranged_items.append(wpn);
    current_phase_ranged_items.append(wpn);
}

void EquipmentDb::add_ring(Item* ring) {
    add_item_id(ring);
    rings.append(ring);
    current_phase_rings.append(ring);
}

Weapon* EquipmentDb::get_melee_weapon(const int item_id) const {
    for (const auto& current_phase_mh_slot_item : current_phase_mh_slot_items) {
        if (item_id == current_phase_mh_slot_item->item_id)
            return new Weapon(static_cast<Weapon*>(current_phase_mh_slot_item));
    }

    for (const auto& current_phase_oh_slot_item : current_phase_oh_slot_items) {
        if (item_id == current_phase_oh_slot_item->item_id)
            return new Weapon(static_cast<Weapon*>(current_phase_oh_slot_item));
    }

    return nullptr;
}

Item* EquipmentDb::get_item(const QVector<Item*>& item_list, const int item_id) const {
    for (const auto item : item_list) {
        if (item_id == item->item_id)
            return new Item(item);
    }

    return nullptr;
}

Weapon* EquipmentDb::get_ranged(const int item_id) const {
    for (const auto& current_phase_ranged_slot_item : current_phase_ranged_items) {
        if (item_id == current_phase_ranged_slot_item->item_id)
            return new Weapon(static_cast<Weapon*>(current_phase_ranged_slot_item));
    }

    return nullptr;
}

Item* EquipmentDb::get_head(const int item_id) const {
    return get_item(current_phase_helms, item_id);
}

Item* EquipmentDb::get_neck(const int item_id) const {
    return get_item(current_phase_amulets, item_id);
}

Item* EquipmentDb::get_shoulders(const int item_id) const {
    return get_item(current_phase_shoulders, item_id);
}

Item* EquipmentDb::get_back(const int item_id) const {
    return get_item(current_phase_backs, item_id);
}

Item* EquipmentDb::get_chest(const int item_id) const {
    return get_item(current_phase_chests, item_id);
}

Item* EquipmentDb::get_wrist(const int item_id) const {
    return get_item(current_phase_wrists, item_id);
}

Item* EquipmentDb::get_gloves(const int item_id) const {
    return get_item(current_phase_gloves, item_id);
}

Item* EquipmentDb::get_belt(const int item_id) const {
    return get_item(current_phase_belts, item_id);
}

Item* EquipmentDb::get_legs(const int item_id) const {
    return get_item(current_phase_legs, item_id);
}

Item* EquipmentDb::get_boots(const int item_id) const {
    return get_item(current_phase_boots, item_id);
}

Item* EquipmentDb::get_ring(const int item_id) const {
    return get_item(current_phase_rings, item_id);
}

Item* EquipmentDb::get_trinket(const int item_id) const {
    return get_item(current_phase_trinkets, item_id);
}

Item* EquipmentDb::get_caster_offhand(const int item_id) const {
    return get_item(current_phase_oh_slot_items, item_id);
}

Item* EquipmentDb::get_relic(const int item_id) const {
    return get_item(current_phase_relics, item_id);
}

Projectile* EquipmentDb::get_projectile(const int item_id) const {
    for (const auto& current_phase_projectile : current_phase_projectiles) {
        if (item_id == current_phase_projectile->item_id)
            return new Projectile(static_cast<Projectile*>(current_phase_projectile));
    }

    return nullptr;
}

Quiver* EquipmentDb::get_quiver(const int item_id) const {
    for (const auto& current_phase_quiver : current_phase_quivers) {
        if (item_id == current_phase_quiver->item_id)
            return new Quiver(static_cast<Quiver*>(current_phase_quiver));
    }

    return nullptr;
}

Item* EquipmentDb::get_shield(const int item_id) const {
    return get_item(current_phase_shields, item_id);
}

Item* EquipmentDb::get_item(const int item_id) const {
    if (item_id_to_item.contains(item_id))
        return item_id_to_item[item_id];

    return nullptr;
}

const QVector<Item*>& EquipmentDb::get_slot_items(const int slot) const {
    switch (slot) {
    case ItemSlots::MAINHAND:
        return current_phase_mh_slot_items;
    case ItemSlots::OFFHAND:
        return current_phase_oh_slot_items;
    case ItemSlots::RANGED:
        return current_phase_ranged_items;
    case ItemSlots::HEAD:
        return current_phase_helms;
    case ItemSlots::NECK:
        return current_phase_amulets;
    case ItemSlots::SHOULDERS:
        return current_phase_shoulders;
    case ItemSlots::BACK:
        return current_phase_backs;
    case ItemSlots::CHEST:
        return current_phase_chests;
    case ItemSlots::WRIST:
        return current_phase_wrists;
    case ItemSlots::GLOVES:
        return current_phase_gloves;
    case ItemSlots::BELT:
        return current_phase_belts;
    case ItemSlots::LEGS:
        return current_phase_legs;
    case ItemSlots::BOOTS:
        return current_phase_boots;
    case ItemSlots::RING:
        return current_phase_rings;
    case ItemSlots::TRINKET:
        return current_phase_trinkets;
    case ItemSlots::PROJECTILE:
        return current_phase_projectiles;
    case ItemSlots::RELIC:
        return current_phase_relics;
    case ItemSlots::QUIVER:
        return current_phase_quivers;
    case ItemSlots::SHIELD:
        return current_phase_shields;
    }

    return current_phase_amulets;
}

QString EquipmentDb::get_name_for_item_id(const int item_id) const {
    check((item_id_to_item.contains(item_id)), QString("Unknown item id '%1'").arg(item_id).toStdString());

    return item_id_to_item[item_id]->name;
}

void EquipmentDb::set_content_phase(const Content::Phase phase) {
    this->current_phase = phase;

    set_phase_for_slot(mh_slot_items, current_phase_mh_slot_items);
    set_phase_for_slot(oh_slot_items, current_phase_oh_slot_items);
    set_phase_for_slot(ranged_items, current_phase_ranged_items);
    set_phase_for_slot(helms, current_phase_helms);
    set_phase_for_slot(amulets, current_phase_amulets);
    set_phase_for_slot(shoulders, current_phase_shoulders);
    set_phase_for_slot(backs, current_phase_backs);
    set_phase_for_slot(chests, current_phase_chests);
    set_phase_for_slot(wrists, current_phase_wrists);
    set_phase_for_slot(gloves, current_phase_gloves);
    set_phase_for_slot(belts, current_phase_belts);
    set_phase_for_slot(legs, current_phase_legs);
    set_phase_for_slot(boots, current_phase_boots);
    set_phase_for_slot(rings, current_phase_rings);
    set_phase_for_slot(trinkets, current_phase_trinkets);
    set_phase_for_slot(projectiles, current_phase_projectiles);
    set_phase_for_slot(relics, current_phase_relics);
    set_phase_for_slot(quivers, current_phase_quivers);
    set_phase_for_slot(shields, current_phase_shields);
}

void EquipmentDb::set_phase_for_slot(QVector<Item*>& total_slot_items, QVector<Item*>& phase_slot_items) {
    phase_slot_items.clear();
    QMap<int, Item*> tmp_items;

    for (const auto& item : total_slot_items) {
        if (item->valid_for_phase(current_phase)) {
            if (tmp_items.contains(item->item_id)) {
                QString curr_tmp_phase = tmp_items[item->item_id]->get_value("phase");
                QString contender_phase = item->get_value("phase");

                if (QVersionNumber::fromString(contender_phase) < QVersionNumber::fromString(curr_tmp_phase))
                    continue;
            }
            tmp_items[item->item_id] = item;
        }
    }

    for (const auto& item : tmp_items)
        phase_slot_items.append(item);
}

void EquipmentDb::read_equipment_files() {
    QFile file("equipment_paths.xml");

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Error opening" << file.fileName() << "in" << QDir::currentPath();
        qDebug() << file.errorString() << "\n";
        qDebug() << "Verify the paths in 'build.config' are correct and run 'DevTools/copy_to_debug.py'.";
        qDebug() << "For more information see: https://github.com/timhul/ClassicSim/wiki/Developer-Information";
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
            } else {
                qDebug() << "Skipping element" << reader.readElementText();
                reader.skipCurrentElement();
            }
        }
    } else
        qDebug() << "Failed to read equipment_paths.xml.";

    file.close();

    if (equipment_file_paths.empty())
        qDebug() << "Failed to find equipment files in equipment_paths.xml";

    QVector<Item*> items;

    for (const auto& equipment_file_path : equipment_file_paths) {
        ItemFileReader(enchant_info).read_items(items, equipment_file_path);
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
    take_items_of_slot_from_given_items(items, relics, ItemSlots::RELIC);
    take_items_of_slot_from_given_items(items, oh_slot_items, ItemSlots::CASTER_OFFHAND);
    take_items_of_slot_from_given_items(items, quivers, ItemSlots::QUIVER);
    take_items_of_slot_from_given_items(items, shields, ItemSlots::SHIELD);

    for (const auto& item : items) {
        qDebug() << "Failed to classify slot for" << item->name;
        delete item;
    }
}

void EquipmentDb::take_weapons_from_given_items(QVector<Item*>& mixed_items) {
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
            oh_slot_items.append(new Weapon(static_cast<Weapon*>(item)));
            add_item_id(item);
            --i;
            break;
        case WeaponSlots::RANGED:
            item = mixed_items.takeAt(i);
            ranged_items.append(new Weapon(static_cast<Weapon*>(item)));
            add_item_id(item);
            --i;
            break;
        }
    }
}

void EquipmentDb::take_items_of_slot_from_given_items(QVector<Item*>& mixed_items, QVector<Item*>& sorted, const int slot) {
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
