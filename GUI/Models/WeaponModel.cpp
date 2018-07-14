
#include "WeaponModel.h"
#include "Weapon.h"
#include "EquipmentDb.h"
#include "ItemTypeFilterModel.h"
#include <QDebug>

WeaponModel::WeaponModel(EquipmentDb* db, ItemTypeFilterModel* item_type_filter_model, QObject *parent)
    : QAbstractListModel(parent)
{
    this->db = db;
    this->item_type_filter_model = item_type_filter_model;
    this->slot = ItemSlots::MAINHAND;
}

bool dps(Weapon* lhs, Weapon* rhs) {
    return lhs->get_wpn_dps() > rhs->get_wpn_dps();
}

bool speed(Weapon* lhs, Weapon* rhs) {
    return lhs->get_base_weapon_speed() > rhs->get_base_weapon_speed();
}

bool name(Weapon* lhs, Weapon* rhs) {
    return lhs->get_name() > rhs->get_name();
}

void WeaponModel::update_items() {
    addWeapons(this->db);
}

void WeaponModel::set_patch(const QString &patch) {
    db->set_patch(patch);
    update_items();
}

void WeaponModel::setSlot(const int slot) {
    this->slot = slot;
    update_items();
}

void WeaponModel::addWeapons(const EquipmentDb* db) {
    if (melee_weapons.size() > 0) {
        beginRemoveRows(QModelIndex(), 0, melee_weapons.size() - 1);
        melee_weapons.clear();
        endRemoveRows();
    }

    QVector<Item*> wpns = db->get_slot_items(slot);

    for (int i = 0; i < wpns.size(); ++i) {
        if (item_type_filter_model->get_filter_active(wpns[i]->get_item_type()))
            continue;

        addWeapon(dynamic_cast<Weapon*>(wpns[i]));
    }

    layoutAboutToBeChanged();
    std::sort(melee_weapons.begin(), melee_weapons.end(), dps);
    layoutChanged();
}

void WeaponModel::addWeapon(Weapon* weapon)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    melee_weapons << weapon;
    endInsertRows();
}

int WeaponModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return melee_weapons.count();
}

QVariant WeaponModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= melee_weapons.count())
        return QVariant();

    const Weapon* weapon = melee_weapons[index.row()];

    if (role == NameRole)
        return weapon->get_name();
    if (role == SpeedRole)
        return QString::number(weapon->get_base_weapon_speed(), 'f', 1 );
    if (role == DpsRole)
        return QString::number(weapon->get_wpn_dps(), 'f', 1 );
    if (role == PatchRole)
        return weapon->get_value("patch");
    if (role == SourceRole)
        return weapon->get_value("source");
    if (role == TypeRole)
        return weapon->get_value("type");
    if (role == ReqLvlRole)
        return weapon->get_value("req_lvl");
    if (role == ItemLvlRole)
        return weapon->get_value("item_lvl");
    if (role == QualityRole)
        return weapon->get_value("quality");
    if (role == IconRole)
        return weapon->get_value("icon");

    return QVariant();
}

QHash<int, QByteArray> WeaponModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[SpeedRole] = "speed";
    roles[DpsRole] = "dps";
    roles[PatchRole] = "patch";
    roles[SourceRole] = "source";
    roles[TypeRole] = "type";
    roles[ReqLvlRole] = "req_lvl";
    roles[ItemLvlRole] = "item_lvl";
    roles[QualityRole] = "quality";
    roles[IconRole] = "icon";
    return roles;
}
