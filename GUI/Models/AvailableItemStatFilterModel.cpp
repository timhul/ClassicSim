
#include "AvailableItemStatFilterModel.h"
#include "ActiveItemStatFilterModel.h"
#include "Item.h"
#include "ItemModel.h"
#include "WeaponModel.h"
#include "EquipmentDb.h"
#include "Character.h"

AvailableItemStatFilterModel::AvailableItemStatFilterModel(ActiveItemStatFilterModel* active_stat_model, QObject *parent)
    : QAbstractListModel(parent)
{
    this->active_stat_model = active_stat_model;
    add_available_stat_filters();
}

AvailableItemStatFilterModel::~AvailableItemStatFilterModel() {
    for (auto & filter : available_item_stat_filters) {
        delete filter;
    }

    available_item_stat_filters.clear();
}

void AvailableItemStatFilterModel::addStatFilter(int index) {
    if (index < 0 || index >= available_item_stat_filters.size())
        return;

    auto stat_filter = available_item_stat_filters[index];
    this->active_stat_model->add_filter(stat_filter->item_stat_flag, stat_filter->description);
}

int AvailableItemStatFilterModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return available_item_stat_filters.count();
}

QVariant AvailableItemStatFilterModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= available_item_stat_filters.count())
        return QVariant();

    if (role == IndexRole)
        return index.row();
    if (role == DescriptionRole)
        return available_item_stat_filters[index.row()]->description;

    return QVariant();
}

QHash<int, QByteArray> AvailableItemStatFilterModel::roleNames() const {
    QHash<int, QByteArray> roles;

    roles[IndexRole] = "index";
    roles[DescriptionRole] = "description";

    return roles;
}

void AvailableItemStatFilterModel::add_available_stat_filters() {
    // TODO: Consider grouping these such that phys dps/magical dps/healer/tank can be separated.

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    available_item_stat_filters.append(new AvailableStatFilter(ItemStats::Agility, "Agility"));
    available_item_stat_filters.append(new AvailableStatFilter(ItemStats::Stamina, "Stamina"));
    available_item_stat_filters.append(new AvailableStatFilter(ItemStats::Strength, "Strength"));
    available_item_stat_filters.append(new AvailableStatFilter(ItemStats::SkillAxe, "Axe Skill"));
    available_item_stat_filters.append(new AvailableStatFilter(ItemStats::SkillDagger, "Dagger Skill"));
    available_item_stat_filters.append(new AvailableStatFilter(ItemStats::SkillMace, "Mace Skill"));
    available_item_stat_filters.append(new AvailableStatFilter(ItemStats::SkillSword, "Sword Skill"));
    available_item_stat_filters.append(new AvailableStatFilter(ItemStats::HitChance, "%Hit Chance"));
    available_item_stat_filters.append(new AvailableStatFilter(ItemStats::CritChance, "%Critical Strike"));
    available_item_stat_filters.append(new AvailableStatFilter(ItemStats::AttackPower, "Attack Power"));
    endInsertRows();
}
