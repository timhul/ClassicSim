
#include "WeaponModel.h"
#include "Weapon.h"
#include "EquipmentDb.h"
#include "ActiveItemStatFilterModel.h"
#include "ItemTypeFilterModel.h"
#include <QVersionNumber>

WeaponModel::WeaponModel(EquipmentDb* db,
                         ItemTypeFilterModel* item_type_filter_model,
                         ActiveItemStatFilterModel* item_stat_filter_model,
                         QObject *parent)
    : QAbstractListModel(parent)
{
    this->db = db;
    this->item_stat_filter_model = item_stat_filter_model;
    this->item_type_filter_model = item_type_filter_model;
    this->slot = ItemSlots::MAINHAND;

    this->current_sorting_method = WeaponSorting::Methods::ByIlvl;
    this->sorting_methods.insert(WeaponSorting::Methods::ByIlvl, true);
    this->sorting_methods.insert(WeaponSorting::Methods::ByName, false);
    this->sorting_methods.insert(WeaponSorting::Methods::ByDps, false);
    this->sorting_methods.insert(WeaponSorting::Methods::BySpeed, false);
    this->sorting_methods.insert(WeaponSorting::Methods::ByPatch, false);
    this->sorting_methods.insert(WeaponSorting::Methods::ByItemType, false);
}

bool name(Weapon* lhs, Weapon* rhs) {
    return lhs->get_name() < rhs->get_name();
}

double delta(double first, double second) {
    first = first - second;
    return first < 0 ? first * -1 : first;
}

bool ilvl(Weapon* lhs, Weapon* rhs) {
    auto lhs_ilvl = lhs->get_value("item_lvl");
    auto rhs_ilvl = rhs->get_value("item_lvl");

    return lhs_ilvl == rhs_ilvl ? name(lhs, rhs) : lhs_ilvl > rhs_ilvl;
}

bool dps(Weapon* lhs, Weapon* rhs) {
    auto lhs_dps = lhs->get_wpn_dps();
    auto rhs_dps = rhs->get_wpn_dps();

    return (delta(lhs_dps, rhs_dps)) < 0.001 ? ilvl(lhs, rhs) : lhs_dps > rhs_dps;
}

bool speed(Weapon* lhs, Weapon* rhs) {
    auto lhs_speed = lhs->get_base_weapon_speed();
    auto rhs_speed = rhs->get_base_weapon_speed();

    return (delta(lhs_speed, rhs_speed)) < 0.001 ? ilvl(lhs, rhs) : lhs_speed > rhs_speed;
}

bool patch(Weapon* lhs, Weapon* rhs) {
    auto lhs_patch = QVersionNumber::fromString(lhs->get_value("patch"));
    auto rhs_patch = QVersionNumber::fromString(rhs->get_value("patch"));

    return lhs_patch == rhs_patch ? ilvl(lhs, rhs) : lhs_patch > rhs_patch;
}

bool item_type(Weapon* lhs, Weapon* rhs) {
    auto lhs_itemtype = lhs->get_weapon_type();
    auto rhs_itemtype = rhs->get_weapon_type();

    return lhs_itemtype == rhs_itemtype ? ilvl(lhs, rhs) : lhs_itemtype > rhs_itemtype;
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

int WeaponModel::get_current_sorting_method() const {
    return static_cast<int>(current_sorting_method);
}

void WeaponModel::selectSort(const int method) {
    layoutAboutToBeChanged();

    auto sorting_method = static_cast<WeaponSorting::Methods>(method);
    switch (sorting_method) {
    case WeaponSorting::Methods::ByIlvl:
        std::sort(melee_weapons.begin(), melee_weapons.end(), ilvl);
        select_new_method(WeaponSorting::Methods::ByIlvl);
        break;
    case WeaponSorting::Methods::ByName:
        std::sort(melee_weapons.begin(), melee_weapons.end(), name);
        select_new_method(WeaponSorting::Methods::ByName);
        break;
    case WeaponSorting::Methods::ByDps:
        std::sort(melee_weapons.begin(), melee_weapons.end(), dps);
        select_new_method(WeaponSorting::Methods::ByDps);
        break;
    case WeaponSorting::Methods::BySpeed:
        std::sort(melee_weapons.begin(), melee_weapons.end(), speed);
        select_new_method(WeaponSorting::Methods::BySpeed);
        break;
    case WeaponSorting::Methods::ByPatch:
        std::sort(melee_weapons.begin(), melee_weapons.end(), patch);
        select_new_method(WeaponSorting::Methods::ByPatch);
        break;
    case WeaponSorting::Methods::ByItemType:
        std::sort(melee_weapons.begin(), melee_weapons.end(), item_type);
        select_new_method(WeaponSorting::Methods::ByItemType);
        break;
    }

    layoutChanged();
}

void WeaponModel::select_new_method(const WeaponSorting::Methods new_method) {
    if (sorting_methods[new_method])
        std::reverse(melee_weapons.begin(), melee_weapons.end());

    sorting_methods[new_method] = !sorting_methods[new_method];
    current_sorting_method = new_method;

    QHash<WeaponSorting::Methods, bool>::iterator it = sorting_methods.begin();
    while (it != sorting_methods.end()) {
        if (it.key() != new_method) {
            sorting_methods[it.key()] = false;
        }
        ++it;
    }

    Q_EMIT sortingMethodChanged();
}

void WeaponModel::addWeapons(const EquipmentDb* db) {
    if (!melee_weapons.empty()) {
        beginRemoveRows(QModelIndex(), 0, melee_weapons.size() - 1);
        melee_weapons.clear();
        endRemoveRows();
    }

    QVector<Item*> wpns = db->get_slot_items(slot);

    for (auto & wpn : wpns) {
        if (item_type_filter_model->get_filter_active(wpn->get_item_type()))
            continue;

        if (item_stat_filter_model->item_passes_active_stat_filters(wpn))
            addWeapon(dynamic_cast<Weapon*>(wpn));
    }

    layoutAboutToBeChanged();
    std::sort(melee_weapons.begin(), melee_weapons.end(), ilvl);
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
