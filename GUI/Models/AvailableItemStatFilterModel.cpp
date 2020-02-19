
#include "AvailableItemStatFilterModel.h"

#include "ActiveItemStatFilterModel.h"
#include "Character.h"
#include "EquipmentDb.h"
#include "Item.h"
#include "ItemModel.h"
#include "WeaponModel.h"

AvailableItemStatFilterModel::AvailableItemStatFilterModel(ActiveItemStatFilterModel* active_stat_model, QObject* parent) :
    QAbstractListModel(parent) {
    this->active_stat_model = active_stat_model;
    add_available_stat_filters();
}

AvailableItemStatFilterModel::~AvailableItemStatFilterModel() {
    for (const auto& filter : available_item_stat_filters) {
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

int AvailableItemStatFilterModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return available_item_stat_filters.count();
}

QVariant AvailableItemStatFilterModel::data(const QModelIndex& index, int role) const {
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
    available_item_stat_filters.append(new AvailableStatFilter(ItemStats::SpellDamage, "+Spell Damage"));
    available_item_stat_filters.append(new AvailableStatFilter(ItemStats::SpellDamageArcane, "+Arcane Damage"));
    available_item_stat_filters.append(new AvailableStatFilter(ItemStats::SpellDamageFire, "+Fire Damage"));
    available_item_stat_filters.append(new AvailableStatFilter(ItemStats::SpellDamageFrost, "+Frost Damage"));
    available_item_stat_filters.append(new AvailableStatFilter(ItemStats::SpellDamageNature, "+Nature Damage"));
    available_item_stat_filters.append(new AvailableStatFilter(ItemStats::SpellDamageShadow, "+Shadow Damage"));
    available_item_stat_filters.append(new AvailableStatFilter(ItemStats::SpellHit, "+% Spell Hit"));
    available_item_stat_filters.append(new AvailableStatFilter(ItemStats::SpellCrit, "+% Spell Crit"));
    available_item_stat_filters.append(new AvailableStatFilter(ItemStats::ManaPer5, "+Mana per 5"));
    endInsertRows();
}
