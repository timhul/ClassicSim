#include "ItemTypeFilterModel.h"

#include <QDebug>

#include "Character.h"
#include "EquipmentDb.h"
#include "Item.h"
#include "Utils/Check.h"

ItemTypeFilterModel::ItemTypeFilterModel(QObject *parent)
    : QAbstractListModel(parent),
      pchar(nullptr),
      last_toggled(-1)
{
    check((EquipmentSlot::MAINHAND == 0), "Update EquipmentSlot::MAINHAND value");
    check((EquipmentSlot::PROJECTILE == 17), "Update EquipmentSlot::AMMO value");
    for (int i = 0; i < EquipmentSlot::PROJECTILE + 1; ++i)
        item_type_filters.append(QList<ItemTypeFilter>());
}

void ItemTypeFilterModel::set_character(Character *pchar) {
    beginResetModel();
    for (auto & list : item_type_filters)
        list.clear();
    endResetModel();

    this->pchar = pchar;

    for (int i = 0; i < EquipmentSlot::PROJECTILE + 1; ++i) {
        equipment_slot = i;
        add_item_type_filters();
    }

    equipment_slot = ItemSlots::MAINHAND;
    set_item_slot(equipment_slot);
}

bool ItemTypeFilterModel::get_item_type_valid(const int item_type) const {
    if (item_type_filters[equipment_slot].empty())
        return true;

    for (const auto & i : item_type_filters[equipment_slot]) {
        if (i.item_type == item_type)
            return true;
    }

    return false;
}

bool ItemTypeFilterModel::get_filter_active(const int item_type) const {
    for (const auto & i : item_type_filters[equipment_slot]) {
        if (i.item_type == item_type) {
            return i.active;
        }
    }

    return false;
}

void ItemTypeFilterModel::toggle_single_filter(const int item_type) {
    for (int i = 0; i < item_type_filters[equipment_slot].size(); ++i) {
        if (item_type_filters[equipment_slot][i].item_type == item_type) {
            item_type_filters[equipment_slot][i].active = !item_type_filters[equipment_slot][i].active;
            last_toggled = i;
            return;
        }
    }

    qDebug() << "ItemTypeFilterModel::toggle_single_filter: could not find filter" << item_type;
}

void ItemTypeFilterModel::select_range_of_filters(const int filter) {
    int target_index = -1;

    for (int i = 0; i < item_type_filters[equipment_slot].size(); ++i) {
        if (item_type_filters[equipment_slot][i].item_type == filter) {
            target_index = i;
            break;
        }
    }

    if (target_index == last_toggled || target_index == -1)
        return;

    if (last_toggled == -1) {
        last_toggled = target_index;
        return;
    }

    if (target_index > last_toggled) {
        for (int i = last_toggled; i <= target_index; ++i)
            item_type_filters[equipment_slot][i].active = false;
    }
    else {
        for (int i = last_toggled; i >= target_index; --i)
            item_type_filters[equipment_slot][i].active = false;
    }

    last_toggled = target_index;
}

void ItemTypeFilterModel::clear_filters_and_select_single_filter(const int filter) {
    layoutAboutToBeChanged();
    for (int i = 0; i < item_type_filters[equipment_slot].size(); ++i) {
        if (item_type_filters[equipment_slot][i].item_type == filter) {
            item_type_filters[equipment_slot][i].active = false;
            last_toggled = i;
        }
        else
            item_type_filters[equipment_slot][i].active = true;
    }

    layoutChanged();
}

void ItemTypeFilterModel::set_item_slot(const int item_slot) {
    layoutAboutToBeChanged();
    this->equipment_slot = item_slot;
    layoutChanged();
    last_toggled = -1;
}

void ItemTypeFilterModel::add_item_type_filters() {
    switch (equipment_slot) {
    case EquipmentSlot::HEAD:
    case EquipmentSlot::SHOULDERS:
    case EquipmentSlot::CHEST:
    case EquipmentSlot::WRIST:
    case EquipmentSlot::GLOVES:
    case EquipmentSlot::BELT:
    case EquipmentSlot::LEGS:
    case EquipmentSlot::BOOTS:
        add_armor_item_type_filters();
        break;
    case EquipmentSlot::MAINHAND:
    case EquipmentSlot::OFFHAND:
    case EquipmentSlot::RANGED:
        add_weapon_item_type_filters();
        break;
    }
}

void ItemTypeFilterModel::add_armor_item_type_filters() {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    switch (pchar->get_highest_possible_armor_type()) {
    case ArmorTypes::PLATE:
        item_type_filters[equipment_slot].append(ItemTypeFilter(ArmorTypes::PLATE, "Plate"));
        // C++17 [[clang::fallthrough]];
    case ArmorTypes::MAIL:
        item_type_filters[equipment_slot].append(ItemTypeFilter(ArmorTypes::MAIL, "Mail"));
        // C++17 [[clang::fallthrough]];
    case ArmorTypes::LEATHER:
        item_type_filters[equipment_slot].append(ItemTypeFilter(ArmorTypes::LEATHER, "Leather"));
        // C++17 [[clang::fallthrough]];
    case ArmorTypes::CLOTH:
        item_type_filters[equipment_slot].append(ItemTypeFilter(ArmorTypes::CLOTH, "Cloth"));
    }

    std::reverse(item_type_filters[equipment_slot].begin(), item_type_filters[equipment_slot].end());

    endInsertRows();
}

void ItemTypeFilterModel::add_weapon_item_type_filters() {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    QVector<int> available_types = pchar->get_weapon_proficiencies_for_slot(equipment_slot);

    for (int available_type : available_types) {
        switch (available_type) {
        case WeaponTypes::AXE:
            item_type_filters[equipment_slot].append(ItemTypeFilter(WeaponTypes::AXE, "Axe"));
            break;
        case WeaponTypes::BOW:
            item_type_filters[equipment_slot].append(ItemTypeFilter(WeaponTypes::BOW, "Bow"));
            break;
        case WeaponTypes::CASTER_OFFHAND:
            item_type_filters[equipment_slot].append(ItemTypeFilter(WeaponTypes::CASTER_OFFHAND, "Offhand"));
            break;
        case WeaponTypes::CROSSBOW:
            item_type_filters[equipment_slot].append(ItemTypeFilter(WeaponTypes::CROSSBOW, "Crossbow"));
            break;
        case WeaponTypes::DAGGER:
            item_type_filters[equipment_slot].append(ItemTypeFilter(WeaponTypes::DAGGER, "Dagger"));
            break;
        case WeaponTypes::FIST:
            item_type_filters[equipment_slot].append(ItemTypeFilter(WeaponTypes::FIST, "Fist"));
            break;
        case WeaponTypes::GUN:
            item_type_filters[equipment_slot].append(ItemTypeFilter(WeaponTypes::GUN, "Gun"));
            break;
        case WeaponTypes::MACE:
            item_type_filters[equipment_slot].append(ItemTypeFilter(WeaponTypes::MACE, "Mace"));
            break;
        case WeaponTypes::POLEARM:
            item_type_filters[equipment_slot].append(ItemTypeFilter(WeaponTypes::POLEARM, "Polearm"));
            break;
        case WeaponTypes::SHIELD:
            item_type_filters[equipment_slot].append(ItemTypeFilter(WeaponTypes::SHIELD, "Shield"));
            break;
        case WeaponTypes::STAFF:
            item_type_filters[equipment_slot].append(ItemTypeFilter(WeaponTypes::STAFF, "Staff"));
            break;
        case WeaponTypes::SWORD:
            item_type_filters[equipment_slot].append(ItemTypeFilter(WeaponTypes::SWORD, "Sword"));
            break;
        case WeaponTypes::THROWN:
            item_type_filters[equipment_slot].append(ItemTypeFilter(WeaponTypes::THROWN, "Thrown"));
            break;
        case WeaponTypes::TWOHAND_AXE:
            item_type_filters[equipment_slot].append(ItemTypeFilter(WeaponTypes::TWOHAND_AXE, "Two-hand Axe"));
            break;
        case WeaponTypes::TWOHAND_MACE:
            item_type_filters[equipment_slot].append(ItemTypeFilter(WeaponTypes::TWOHAND_MACE, "Two-hand Mace"));
            break;
        case WeaponTypes::TWOHAND_SWORD:
            item_type_filters[equipment_slot].append(ItemTypeFilter(WeaponTypes::TWOHAND_SWORD, "Two-hand Sword"));
            break;
        }
    }

    endInsertRows();
}

int ItemTypeFilterModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return item_type_filters[equipment_slot].count();
}

QVariant ItemTypeFilterModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= item_type_filters[equipment_slot].count())
        return QVariant();

    if (role == ItemTypeRole)
        return item_type_filters[equipment_slot][index.row()].item_type;
    if (role == DescriptionRole)
        return item_type_filters[equipment_slot][index.row()].name;
    if (role == ActiveRole)
        return item_type_filters[equipment_slot][index.row()].active;

    return QVariant();
}

QHash<int, QByteArray> ItemTypeFilterModel::roleNames() const {
    QHash<int, QByteArray> roles;

    roles[ItemTypeRole] = "item_type";
    roles[DescriptionRole] = "desc";
    roles[ActiveRole] = "active";

    return roles;
}
