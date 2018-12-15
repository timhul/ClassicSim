#include "EnchantModel.h"

#include "Character.h"
#include "CharacterEnchants.h"

EnchantModel::EnchantModel(const int equipment_slot, const bool permanent, QObject *parent) :
    QAbstractListModel(parent),
    equipment_slot(equipment_slot),
    permanent(permanent)
{}

int EnchantModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return enchants.count();
}

void EnchantModel::set_character(Character* pchar) {
    beginResetModel();
    enchants.clear();
    enchants = permanent ? pchar->get_enchants()->get_available_enchants(equipment_slot) :
                           pchar->get_enchants()->get_available_temp_enchants(equipment_slot);
    endResetModel();
}

QVariant EnchantModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= enchants.count())
        return QVariant();

    if (role == NameRole)
        return EnchantName::get_name(enchants[index.row()]);
    if (role == EffectRole)
        return EnchantName::get_effect(enchants[index.row()]);
    if (role == EnumRole)
        return enchants[index.row()];

    return QVariant();
}

QHash<int, QByteArray> EnchantModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "_name";
    roles[EffectRole] = "_descr";
    roles[EnumRole] = "_enum";
    return roles;
}
