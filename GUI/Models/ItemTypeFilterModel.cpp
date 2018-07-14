
#include "ItemTypeFilterModel.h"
#include "Item.h"
#include "EquipmentDb.h"
#include "Character.h"
#include <QDebug>

ItemTypeFilterModel::ItemTypeFilterModel(QObject *parent)
    : QAbstractListModel(parent),
      item_slot(ItemSlots::MAINHAND),
      pchar(nullptr)
{}

void ItemTypeFilterModel::set_character(Character *pchar) {
    this->pchar = pchar;
    set_item_slot(item_slot);
}

bool ItemTypeFilterModel::get_filter_active(const int filter) const {
    if (filter < 0 || filter >= item_type_filters.size()) {
        qDebug() << "ItemTypeFilterModel::get_filter_active(): Filter out of range" << filter;
        return false;
    }

    return item_type_filters[filter].active;
}

void ItemTypeFilterModel::toggle_single_filter(const int filter) {
    if (filter < 0 || filter >= item_type_filters.size()) {
        qDebug() << "Filter out of range" << filter;
        return;
    }

    item_type_filters[filter].active = !item_type_filters[filter].active;
}

void ItemTypeFilterModel::clearCurrentFiltersAndSelectSingleFilter(const int) {

}

void ItemTypeFilterModel::set_item_slot(const int item_slot) {
    this->item_slot = item_slot;
    // Remove all current strings as new item slot means new filters (e.g. from weapon to neck)
    if (item_type_filters.size() > 0) {
        beginRemoveRows(QModelIndex(), 0, item_type_filters.size() - 1);
        item_type_filters.clear();
        endRemoveRows();
    }

    add_item_type_filters();
    layoutChanged();
}

void ItemTypeFilterModel::add_item_type_filters() {
    switch (item_slot) {
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
        item_type_filters.append(ItemFilter(3, "Plate"));
    case ArmorTypes::MAIL:
        item_type_filters.append(ItemFilter(2, "Mail"));
    case ArmorTypes::LEATHER:
        item_type_filters.append(ItemFilter(1, "Leather"));
    case ArmorTypes::CLOTH:
        item_type_filters.append(ItemFilter(0, "Cloth"));
    }

    std::reverse(item_type_filters.begin(), item_type_filters.end());

    endInsertRows();
}

void ItemTypeFilterModel::add_weapon_item_type_filters() {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    QVector<int> available_types = pchar->get_weapon_proficiencies_for_slot(item_slot);

    for (int i = 0; i < available_types.size(); ++i) {
        switch (available_types[i]) {
        case WeaponTypes::AXE:
            item_type_filters.append(ItemFilter(i, "Axe"));
            break;
        case WeaponTypes::BOW:
            item_type_filters.append(ItemFilter(i, "Bow"));
            break;
        case WeaponTypes::CASTER_OFFHAND:
            item_type_filters.append(ItemFilter(i, "Offhand"));
            break;
        case WeaponTypes::CROSSBOW:
            item_type_filters.append(ItemFilter(i, "Crossbow"));
            break;
        case WeaponTypes::DAGGER:
            item_type_filters.append(ItemFilter(i, "Dagger"));
            break;
        case WeaponTypes::FIST:
            item_type_filters.append(ItemFilter(i, "Fist"));
            break;
        case WeaponTypes::GUN:
            item_type_filters.append(ItemFilter(i, "Gun"));
            break;
        case WeaponTypes::MACE:
            item_type_filters.append(ItemFilter(i, "Mace"));
            break;
        case WeaponTypes::POLEARM:
            item_type_filters.append(ItemFilter(i, "Polearm"));
            break;
        case WeaponTypes::SHIELD:
            item_type_filters.append(ItemFilter(i, "Shield"));
            break;
        case WeaponTypes::STAFF:
            item_type_filters.append(ItemFilter(i, "Staff"));
            break;
        case WeaponTypes::SWORD:
            item_type_filters.append(ItemFilter(i, "Sword"));
            break;
        case WeaponTypes::TWOHAND_AXE:
            item_type_filters.append(ItemFilter(i, "Two-hand Axe"));
            break;
        case WeaponTypes::TWOHAND_MACE:
            item_type_filters.append(ItemFilter(i, "Two-hand Mace"));
            break;
        case WeaponTypes::TWOHAND_SWORD:
            item_type_filters.append(ItemFilter(i, "Two-hand Sword"));
            break;
        }
    }

    endInsertRows();
}

int ItemTypeFilterModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return item_type_filters.count();
}

QVariant ItemTypeFilterModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= item_type_filters.count())
        return QVariant();

    if (role == IndexRole)
        return item_type_filters[index.row()].index;
    if (role == DescriptionRole)
        return item_type_filters[index.row()].name;
    if (role == ActiveRole)
        return item_type_filters[index.row()].active;

    return QVariant();
}

QHash<int, QByteArray> ItemTypeFilterModel::roleNames() const {
    QHash<int, QByteArray> roles;

    roles[IndexRole] = "index";
    roles[DescriptionRole] = "desc";
    roles[ActiveRole] = "active";

    return roles;
}
