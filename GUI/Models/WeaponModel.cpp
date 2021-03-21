#include "WeaponModel.h"

#include "ActiveItemStatFilterModel.h"
#include "Character.h"
#include "EquipmentDb.h"
#include "Faction.h"
#include "ItemTypeFilterModel.h"
#include "Utils/CompareDouble.h"
#include "Weapon.h"

WeaponModel::WeaponModel(EquipmentDb* db,
                         ItemTypeFilterModel* item_type_filter_model,
                         ActiveItemStatFilterModel* item_stat_filter_model,
                         QObject* parent) :
    QAbstractListModel(parent),
    slot(ItemSlots::MAINHAND),
    pchar(nullptr),
    db(db),
    item_type_filter_model(item_type_filter_model),
    item_stat_filter_model(item_stat_filter_model) {
    this->current_sorting_method = WeaponSorting::Methods::ByIlvl;

    this->sorting_methods.insert(WeaponSorting::Methods::ByIlvl, true);
    this->sorting_methods.insert(WeaponSorting::Methods::ByName, false);
    this->sorting_methods.insert(WeaponSorting::Methods::ByDps, false);
    this->sorting_methods.insert(WeaponSorting::Methods::BySpeed, false);
    this->sorting_methods.insert(WeaponSorting::Methods::ByPhase, false);
    this->sorting_methods.insert(WeaponSorting::Methods::ByItemType, false);
}

bool name(Weapon* lhs, Weapon* rhs) {
    return lhs->name < rhs->name;
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

bool phase(Weapon* lhs, Weapon* rhs) {
    const int lhs_phase = static_cast<int>(lhs->phase);
    const int rhs_phase = static_cast<int>(rhs->phase);

    return lhs_phase == rhs_phase ? ilvl(lhs, rhs) : lhs_phase > rhs_phase;
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

void WeaponModel::set_phase(const Content::Phase phase) {
    db->set_content_phase(phase);
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
    emit layoutAboutToBeChanged();

    auto sorting_method = static_cast<WeaponSorting::Methods>(method);
    switch (sorting_method) {
    case WeaponSorting::Methods::ByIlvl:
        std::sort(weapons.begin(), weapons.end(), ilvl);
        select_new_method(WeaponSorting::Methods::ByIlvl);
        break;
    case WeaponSorting::Methods::ByName:
        std::sort(weapons.begin(), weapons.end(), name);
        select_new_method(WeaponSorting::Methods::ByName);
        break;
    case WeaponSorting::Methods::ByDps:
        std::sort(weapons.begin(), weapons.end(), dps);
        select_new_method(WeaponSorting::Methods::ByDps);
        break;
    case WeaponSorting::Methods::BySpeed:
        std::sort(weapons.begin(), weapons.end(), speed);
        select_new_method(WeaponSorting::Methods::BySpeed);
        break;
    case WeaponSorting::Methods::ByPhase:
        std::sort(weapons.begin(), weapons.end(), phase);
        select_new_method(WeaponSorting::Methods::ByPhase);
        break;
    case WeaponSorting::Methods::ByItemType:
        std::sort(weapons.begin(), weapons.end(), item_type);
        select_new_method(WeaponSorting::Methods::ByItemType);
        break;
    }

    emit layoutChanged();
}

void WeaponModel::lexicalSearch(const QString& text) {
    auto terms = text.split(QChar(' '), Qt::SplitBehaviorFlags::SkipEmptyParts);
    lexical_search_terms.clear();
    for (const auto& term : terms)
        lexical_search_terms.insert(term.toLower());

    update_items();
}

void WeaponModel::select_new_method(const WeaponSorting::Methods new_method) {
    if (sorting_methods[new_method])
        std::reverse(weapons.begin(), weapons.end());

    sorting_methods[new_method] = !sorting_methods[new_method];
    current_sorting_method = new_method;

    QHash<WeaponSorting::Methods, bool>::const_iterator it = sorting_methods.begin();
    while (it != sorting_methods.end()) {
        if (it.key() != new_method) {
            sorting_methods[it.key()] = false;
        }
        ++it;
    }

    emit sortingMethodChanged();
}

bool WeaponModel::name_passes_lexical_search(const QString& name) {
    const auto lower = name.toLower();
    for (const auto& term : lexical_search_terms) {
        if (!lower.contains(term))
            return false;
    }

    return true;
}

void WeaponModel::update_items() {
    if (!weapons.empty()) {
        beginResetModel();
        weapons.clear();
        endResetModel();
    }

    QVector<Item*> wpns = db->get_slot_items(slot);

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    for (const auto& wpn : wpns) {
        if (!wpn->available_for_faction(static_cast<AvailableFactions::Name>(pchar->get_faction()->get_faction())))
            continue;

        if (!wpn->available_for_class(pchar->class_name))
            continue;

        if (!item_type_filter_model->get_item_type_valid(wpn->get_item_type()))
            continue;

        if (item_type_filter_model->get_filter_active(wpn->get_item_type()))
            continue;

        if (!item_stat_filter_model->item_passes_active_stat_filters(wpn))
            continue;

        if (!name_passes_lexical_search(wpn->base_name))
            continue;

        weapons << static_cast<Weapon*>(wpn);
    }
    endInsertRows();

    emit layoutAboutToBeChanged();
    std::sort(weapons.begin(), weapons.end(), ilvl);
    emit layoutChanged();
}

int WeaponModel::rowCount(const QModelIndex&) const {
    return weapons.count();
}

QVariant WeaponModel::data(const QModelIndex& index, int role) const {
    if (index.row() < 0 || index.row() >= weapons.count())
        return QVariant();

    const Weapon* weapon = weapons[index.row()];

    if (role == IdRole)
        return weapon->item_id;
    if (role == NameRole)
        return weapon->name;
    if (role == SpeedRole)
        return QString::number(weapon->get_base_weapon_speed(), 'f', 1);
    if (role == DpsRole)
        return QString::number(weapon->get_wpn_dps(), 'f', 1);
    if (role == PhaseRole)
        return Content::get_shortname_for_phase(weapon->phase);
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
    if (role == RandomAffixRole)
        return weapon->can_have_random_affix();

    return QVariant();
}

QHash<int, QByteArray> WeaponModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "_itemid";
    roles[NameRole] = "_name";
    roles[SpeedRole] = "_speed";
    roles[DpsRole] = "_dps";
    roles[PhaseRole] = "_phase";
    roles[SourceRole] = "_source";
    roles[TypeRole] = "_type";
    roles[ReqLvlRole] = "_reqlvl";
    roles[ItemLvlRole] = "_itemlvl";
    roles[QualityRole] = "_quality";
    roles[IconRole] = "_icon";
    roles[RandomAffixRole] = "_randomaffix";
    return roles;
}
