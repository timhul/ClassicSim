#include "WeaponModel.h"

#include <QVersionNumber>

#include "ActiveItemStatFilterModel.h"
#include "Character.h"
#include "EquipmentDb.h"
#include "Faction.h"
#include "ItemTypeFilterModel.h"
#include "Weapon.h"

WeaponModel::WeaponModel(EquipmentDb* db,
                         ItemTypeFilterModel* item_type_filter_model,
                         ActiveItemStatFilterModel* item_stat_filter_model,
                         QObject *parent) :
    QAbstractListModel(parent),
    slot(ItemSlots::MAINHAND),
    pchar(nullptr),
    db(db),
    item_type_filter_model(item_type_filter_model),
    item_stat_filter_model(item_stat_filter_model)
{
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

void WeaponModel::set_character(Character* pchar) {
    this->pchar = pchar;
    update_items();
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

void WeaponModel::update_items() {
    if (!melee_weapons.empty()) {
        beginResetModel();
        melee_weapons.clear();
        endResetModel();
    }

    QVector<Item*> wpns = db->get_slot_items(slot);

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    for (auto & wpn : wpns) {
        if (!wpn->available_for_faction(static_cast<AvailableFactions::Name>(pchar->get_faction()->get_faction())))
            continue;

        if (!wpn->available_for_class(pchar->get_name()))
            continue;

        if (!item_type_filter_model->get_item_type_valid(wpn->get_item_type()))
            continue;

        if (item_type_filter_model->get_filter_active(wpn->get_item_type()))
            continue;

        if (item_stat_filter_model->item_passes_active_stat_filters(wpn))
            melee_weapons << dynamic_cast<Weapon*>(wpn);
    }
    endInsertRows();

    layoutAboutToBeChanged();
    std::sort(melee_weapons.begin(), melee_weapons.end(), ilvl);
    layoutChanged();
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
        return weapon->get_weapon_type_string();
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
