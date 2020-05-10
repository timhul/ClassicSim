#include "EnchantModel.h"

#include "Character.h"
#include "CharacterEnchants.h"
#include "ItemNamespace.h"

EnchantModel::EnchantModel(const int equipment_slot, const bool permanent, QObject* parent) :
    QAbstractListModel(parent), pchar(nullptr), enchant_info(EnchantInfo()), equipment_slot(equipment_slot), permanent(permanent) {}

int EnchantModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return enchants.count();
}

void EnchantModel::set_character(Character* pchar) {
    this->pchar = pchar;
    update_enchants();
}

void EnchantModel::update_enchants() {
    beginResetModel();
    enchants.clear();
    enchants = permanent ? pchar->get_enchants()->get_available_enchants(equipment_slot) :
                           pchar->get_enchants()->get_available_temp_enchants(equipment_slot);
    endResetModel();
}

QVariant EnchantModel::data(const QModelIndex& index, int role) const {
    if (index.row() < 0 || index.row() >= enchants.count())
        return QVariant();

    if (role == NameRole)
        return enchant_info.get_display_name(enchants[index.row()]);
    if (role == EffectRole)
        return enchant_info.get_effect(enchants[index.row()]);
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
