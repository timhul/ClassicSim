
#include "WeaponModel.h"
#include "MeleeWeapon.h"
#include "EquipmentDb.h"

WeaponModel::WeaponModel(QObject *parent)
    : QAbstractListModel(parent)
{}

bool dps(MeleeWeapon* lhs, MeleeWeapon* rhs) {
    return lhs->get_wpn_dps() > rhs->get_wpn_dps();
}

bool speed(MeleeWeapon* lhs, MeleeWeapon* rhs) {
    return lhs->get_base_weapon_speed() > rhs->get_base_weapon_speed();
}

bool name(MeleeWeapon* lhs, MeleeWeapon* rhs) {
    return lhs->get_name() > rhs->get_name();
}

void WeaponModel::addWeapons(const EquipmentDb* db) {
    melee_weapons.clear();

    QVector<MeleeWeapon*> wpns = db->get_melee_weapons();

    for (int i = 0; i < wpns.size(); ++i) {
        addWeapon(wpns[i]);
    }

    std::sort(melee_weapons.begin(), melee_weapons.end(), dps);
}

void WeaponModel::addWeapon(MeleeWeapon* weapon)
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

    const MeleeWeapon* weapon = melee_weapons[index.row()];

    if (role == NameRole)
        return weapon->get_name();
    if (role == SpeedRole)
        return QString::number(weapon->get_base_weapon_speed(), 'f', 1 );
    if (role == DpsRole)
        return QString::number(weapon->get_wpn_dps(), 'f', 1 );
    if (role == PatchRole)
        return weapon->get_patch();
    if (role == SourceRole)
        return weapon->get_source();

    return QVariant();
}

QHash<int, QByteArray> WeaponModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[SpeedRole] = "speed";
    roles[DpsRole] = "dps";
    roles[PatchRole] = "patch";
    roles[SourceRole] = "source";
    return roles;
}
