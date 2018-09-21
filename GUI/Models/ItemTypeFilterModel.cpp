
#include "ItemTypeFilterModel.h"
#include "Item.h"
#include "EquipmentDb.h"
#include "Character.h"
#include <QDebug>

ItemTypeFilterModel::ItemTypeFilterModel(QObject *parent)
    : QAbstractListModel(parent),
      pchar(nullptr)
{}

void ItemTypeFilterModel::set_character(Character *pchar) {
    this->pchar = pchar;

    assert(EquipmentSlot::MAINHAND == 0);
    assert(EquipmentSlot::TRINKET2 == 16);
    for (int i = 0; i < 16; ++i) {
        equipment_slot = i;
        item_type_filters.append(QList<ItemFilter>());
        add_item_type_filters();
    }

    equipment_slot = ItemSlots::MAINHAND;

    set_item_slot(equipment_slot);
}

bool ItemTypeFilterModel::get_filter_active(const int filter) const {
    for (int i = 0; i < item_type_filters[equipment_slot].size(); ++i) {
        if (item_type_filters[equipment_slot][i].item_type == filter) {
            return item_type_filters[equipment_slot][i].active;
        }
    }

    return false;
}

void ItemTypeFilterModel::toggle_single_filter(const int filter) {
    for (int i = 0; i < item_type_filters[equipment_slot].size(); ++i) {
        if (item_type_filters[equipment_slot][i].item_type == filter) {
            item_type_filters[equipment_slot][i].active = !item_type_filters[equipment_slot][i].active;
            return;
        }
    }

    qDebug() << "ItemTypeFilterModel::toggle_single_filter: could not find filter" << filter;
}

void ItemTypeFilterModel::clearCurrentFiltersAndSelectSingleFilter(const int) {

}

void ItemTypeFilterModel::set_item_slot(const int item_slot) {
    layoutAboutToBeChanged();
    this->equipment_slot = item_slot;
    layoutChanged();
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
        item_type_filters[equipment_slot].append(ItemFilter(ArmorTypes::PLATE, "Plate"));
        // C++17 [[clang::fallthrough]];
    case ArmorTypes::MAIL:
        item_type_filters[equipment_slot].append(ItemFilter(ArmorTypes::MAIL, "Mail"));
        // C++17 [[clang::fallthrough]];
    case ArmorTypes::LEATHER:
        item_type_filters[equipment_slot].append(ItemFilter(ArmorTypes::LEATHER, "Leather"));
        // C++17 [[clang::fallthrough]];
    case ArmorTypes::CLOTH:
        item_type_filters[equipment_slot].append(ItemFilter(ArmorTypes::CLOTH, "Cloth"));
    }

    std::reverse(item_type_filters[equipment_slot].begin(), item_type_filters[equipment_slot].end());

    endInsertRows();
}

void ItemTypeFilterModel::add_weapon_item_type_filters() {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    QVector<int> available_types = pchar->get_weapon_proficiencies_for_slot(equipment_slot);

    for (int i = 0; i < available_types.size(); ++i) {
        switch (available_types[i]) {
        case WeaponTypes::AXE:
            item_type_filters[equipment_slot].append(ItemFilter(WeaponTypes::AXE, "Axe"));
            break;
        case WeaponTypes::BOW:
            item_type_filters[equipment_slot].append(ItemFilter(WeaponTypes::BOW, "Bow"));
            break;
        case WeaponTypes::CASTER_OFFHAND:
            item_type_filters[equipment_slot].append(ItemFilter(WeaponTypes::CASTER_OFFHAND, "Offhand"));
            break;
        case WeaponTypes::CROSSBOW:
            item_type_filters[equipment_slot].append(ItemFilter(WeaponTypes::CROSSBOW, "Crossbow"));
            break;
        case WeaponTypes::DAGGER:
            item_type_filters[equipment_slot].append(ItemFilter(WeaponTypes::DAGGER, "Dagger"));
            break;
        case WeaponTypes::FIST:
            item_type_filters[equipment_slot].append(ItemFilter(WeaponTypes::FIST, "Fist"));
            break;
        case WeaponTypes::GUN:
            item_type_filters[equipment_slot].append(ItemFilter(WeaponTypes::GUN, "Gun"));
            break;
        case WeaponTypes::MACE:
            item_type_filters[equipment_slot].append(ItemFilter(WeaponTypes::MACE, "Mace"));
            break;
        case WeaponTypes::POLEARM:
            item_type_filters[equipment_slot].append(ItemFilter(WeaponTypes::POLEARM, "Polearm"));
            break;
        case WeaponTypes::SHIELD:
            item_type_filters[equipment_slot].append(ItemFilter(WeaponTypes::SHIELD, "Shield"));
            break;
        case WeaponTypes::STAFF:
            item_type_filters[equipment_slot].append(ItemFilter(WeaponTypes::STAFF, "Staff"));
            break;
        case WeaponTypes::SWORD:
            item_type_filters[equipment_slot].append(ItemFilter(WeaponTypes::SWORD, "Sword"));
            break;
        case WeaponTypes::THROWN:
            item_type_filters[equipment_slot].append(ItemFilter(WeaponTypes::THROWN, "Thrown"));
            break;
        case WeaponTypes::TWOHAND_AXE:
            item_type_filters[equipment_slot].append(ItemFilter(WeaponTypes::TWOHAND_AXE, "Two-hand Axe"));
            break;
        case WeaponTypes::TWOHAND_MACE:
            item_type_filters[equipment_slot].append(ItemFilter(WeaponTypes::TWOHAND_MACE, "Two-hand Mace"));
            break;
        case WeaponTypes::TWOHAND_SWORD:
            item_type_filters[equipment_slot].append(ItemFilter(WeaponTypes::TWOHAND_SWORD, "Two-hand Sword"));
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
