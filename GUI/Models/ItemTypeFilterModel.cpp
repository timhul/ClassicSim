
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
    for (int i = 0; i < item_type_filters.size(); ++i) {
        if (item_type_filters[i].item_type == filter) {
            return item_type_filters[i].active;
        }
    }

    return false;
}

void ItemTypeFilterModel::toggle_single_filter(const int filter) {
    for (int i = 0; i < item_type_filters.size(); ++i) {
        if (item_type_filters[i].item_type == filter) {
            item_type_filters[i].active = !item_type_filters[i].active;
            return;
        }
    }

    qDebug() << "ItemTypeFilterModel::toggle_single_filter: could not find filter" << filter;
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
        item_type_filters.append(ItemFilter(ArmorTypes::PLATE, "Plate"));
    case ArmorTypes::MAIL:
        item_type_filters.append(ItemFilter(ArmorTypes::MAIL, "Mail"));
    case ArmorTypes::LEATHER:
        item_type_filters.append(ItemFilter(ArmorTypes::LEATHER, "Leather"));
    case ArmorTypes::CLOTH:
        item_type_filters.append(ItemFilter(ArmorTypes::CLOTH, "Cloth"));
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
            item_type_filters.append(ItemFilter(WeaponTypes::AXE, "Axe"));
            break;
        case WeaponTypes::BOW:
            item_type_filters.append(ItemFilter(WeaponTypes::BOW, "Bow"));
            break;
        case WeaponTypes::CASTER_OFFHAND:
            item_type_filters.append(ItemFilter(WeaponTypes::CASTER_OFFHAND, "Offhand"));
            break;
        case WeaponTypes::CROSSBOW:
            item_type_filters.append(ItemFilter(WeaponTypes::CROSSBOW, "Crossbow"));
            break;
        case WeaponTypes::DAGGER:
            item_type_filters.append(ItemFilter(WeaponTypes::DAGGER, "Dagger"));
            break;
        case WeaponTypes::FIST:
            item_type_filters.append(ItemFilter(WeaponTypes::FIST, "Fist"));
            break;
        case WeaponTypes::GUN:
            item_type_filters.append(ItemFilter(WeaponTypes::GUN, "Gun"));
            break;
        case WeaponTypes::MACE:
            item_type_filters.append(ItemFilter(WeaponTypes::MACE, "Mace"));
            break;
        case WeaponTypes::POLEARM:
            item_type_filters.append(ItemFilter(WeaponTypes::POLEARM, "Polearm"));
            break;
        case WeaponTypes::SHIELD:
            item_type_filters.append(ItemFilter(WeaponTypes::SHIELD, "Shield"));
            break;
        case WeaponTypes::STAFF:
            item_type_filters.append(ItemFilter(WeaponTypes::STAFF, "Staff"));
            break;
        case WeaponTypes::SWORD:
            item_type_filters.append(ItemFilter(WeaponTypes::SWORD, "Sword"));
            break;
        case WeaponTypes::THROWN:
            item_type_filters.append(ItemFilter(WeaponTypes::THROWN, "Thrown"));
            break;
        case WeaponTypes::TWOHAND_AXE:
            item_type_filters.append(ItemFilter(WeaponTypes::TWOHAND_AXE, "Two-hand Axe"));
            break;
        case WeaponTypes::TWOHAND_MACE:
            item_type_filters.append(ItemFilter(WeaponTypes::TWOHAND_MACE, "Two-hand Mace"));
            break;
        case WeaponTypes::TWOHAND_SWORD:
            item_type_filters.append(ItemFilter(WeaponTypes::TWOHAND_SWORD, "Two-hand Sword"));
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

    if (role == ItemTypeRole)
        return item_type_filters[index.row()].item_type;
    if (role == DescriptionRole)
        return item_type_filters[index.row()].name;
    if (role == ActiveRole)
        return item_type_filters[index.row()].active;

    return QVariant();
}

QHash<int, QByteArray> ItemTypeFilterModel::roleNames() const {
    QHash<int, QByteArray> roles;

    roles[ItemTypeRole] = "item_type";
    roles[DescriptionRole] = "desc";
    roles[ActiveRole] = "active";

    return roles;
}
