#include "ItemModel.h"

#include "ActiveItemStatFilterModel.h"
#include "Character.h"
#include "EquipmentDb.h"
#include "Faction.h"
#include "Item.h"
#include "ItemTypeFilterModel.h"

ItemModel::ItemModel(EquipmentDb* db, ItemTypeFilterModel* item_type_filter_model, ActiveItemStatFilterModel* item_stat_filter_model, QObject* parent) :
    QAbstractListModel(parent),
    slot(ItemSlots::MAINHAND),
    pchar(nullptr),
    db(db),
    item_type_filter_model(item_type_filter_model),
    item_stat_filter_model(item_stat_filter_model) {
    this->current_sorting_method = ItemSorting::Methods::ByIlvl;

    this->sorting_methods.insert(ItemSorting::Methods::ByIlvl, true);
    this->sorting_methods.insert(ItemSorting::Methods::ByName, false);
    this->sorting_methods.insert(ItemSorting::Methods::ByPhase, false);
    this->sorting_methods.insert(ItemSorting::Methods::ByItemType, false);
}

bool name(Item* lhs, Item* rhs) {
    return lhs->name < rhs->name;
}

bool ilvl(Item* lhs, Item* rhs) {
    auto lhs_ilvl = lhs->get_value("item_lvl");
    auto rhs_ilvl = rhs->get_value("item_lvl");

    return lhs_ilvl == rhs_ilvl ? name(lhs, rhs) : lhs_ilvl > rhs_ilvl;
}

bool phase(Item* lhs, Item* rhs) {
    const int lhs_phase = static_cast<int>(lhs->phase);
    const int rhs_phase = static_cast<int>(rhs->phase);

    return lhs_phase == rhs_phase ? ilvl(lhs, rhs) : lhs_phase > rhs_phase;
}

bool item_type(Item* lhs, Item* rhs) {
    auto lhs_itemtype = lhs->get_item_type();
    auto rhs_itemtype = rhs->get_item_type();

    return lhs_itemtype == rhs_itemtype ? ilvl(lhs, rhs) : lhs_itemtype > rhs_itemtype;
}

void ItemModel::set_character(Character* pchar) {
    this->pchar = pchar;
    update_items();
}

void ItemModel::set_phase(const Content::Phase phase) {
    db->set_content_phase(phase);
    update_items();
}

void ItemModel::setSlot(const int slot) {
    this->slot = slot;
    update_items();
}

void ItemModel::selectSort(const int method) {
    emit layoutAboutToBeChanged();

    auto sorting_method = static_cast<ItemSorting::Methods>(method);
    switch (sorting_method) {
    case ItemSorting::Methods::ByIlvl:
        std::sort(items.begin(), items.end(), ilvl);
        select_new_method(ItemSorting::Methods::ByIlvl);
        break;
    case ItemSorting::Methods::ByName:
        std::sort(items.begin(), items.end(), name);
        select_new_method(ItemSorting::Methods::ByName);
        break;
    case ItemSorting::Methods::ByPhase:
        std::sort(items.begin(), items.end(), phase);
        select_new_method(ItemSorting::Methods::ByPhase);
        break;
    case ItemSorting::Methods::ByItemType:
        std::sort(items.begin(), items.end(), item_type);
        select_new_method(ItemSorting::Methods::ByItemType);
        break;
    }

    emit layoutChanged();
}

void ItemModel::lexicalSearch(const QString& text) {
    auto terms = text.split(QChar(' '), Qt::SplitBehaviorFlags::SkipEmptyParts);
    lexical_search_terms.clear();
    for (const auto& term : terms)
        lexical_search_terms.insert(term.toLower());

    update_items();
}

void ItemModel::select_new_method(const ItemSorting::Methods new_method) {
    if (sorting_methods[new_method])
        std::reverse(items.begin(), items.end());

    sorting_methods[new_method] = !sorting_methods[new_method];
    current_sorting_method = new_method;

    QHash<ItemSorting::Methods, bool>::const_iterator it = sorting_methods.begin();
    while (it != sorting_methods.end()) {
        if (it.key() != new_method) {
            sorting_methods[it.key()] = false;
        }
        ++it;
    }

    emit sortingMethodChanged();
}

bool ItemModel::name_passes_lexical_search(const QString& name) {
    const auto lower = name.toLower();
    for (const auto& term : lexical_search_terms) {
        if (!lower.contains(term))
            return false;
    }

    return true;
}

void ItemModel::update_items() {
    if (!items.empty()) {
        beginResetModel();
        items.clear();
        endResetModel();
    }

    QVector<Item*> tmp_items = db->get_slot_items(this->slot);

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    for (const auto& tmp_item : tmp_items) {
        if (!tmp_item->available_for_faction(static_cast<AvailableFactions::Name>(pchar->get_faction()->get_faction())))
            continue;

        if (!tmp_item->available_for_class(pchar->class_name))
            continue;

        if (!item_type_filter_model->get_item_type_valid(tmp_item->get_item_type()))
            continue;

        if (item_type_filter_model->get_filter_active(tmp_item->get_item_type()))
            continue;

        if (!item_stat_filter_model->item_passes_active_stat_filters(tmp_item))
            continue;

        if (!name_passes_lexical_search(tmp_item->base_name))
            continue;

        items << tmp_item;
    }
    endInsertRows();

    emit layoutAboutToBeChanged();
    std::sort(items.begin(), items.end(), ilvl);
    emit layoutChanged();
}

int ItemModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return items.count();
}

QVariant ItemModel::data(const QModelIndex& index, int role) const {
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();

    const Item* item = items[index.row()];

    if (role == IdRole)
        return item->item_id;
    if (role == NameRole)
        return item->name;
    if (role == PhaseRole)
        return Content::get_shortname_for_phase(item->phase);
    if (role == SourceRole)
        return item->get_value("source");
    if (role == TypeRole)
        return item->get_value("type");
    if (role == ReqLvlRole)
        return item->get_value("req_lvl");
    if (role == ItemLvlRole)
        return item->get_value("item_lvl");
    if (role == QualityRole)
        return item->get_value("quality");
    if (role == IconRole)
        return item->get_value("icon");
    if (role == RandomAffixRole)
        return item->can_have_random_affix();

    return QVariant();
}

QHash<int, QByteArray> ItemModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "_itemid";
    roles[NameRole] = "_name";
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
