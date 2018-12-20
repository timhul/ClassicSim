#include "ItemModel.h"

#include "ActiveItemStatFilterModel.h"
#include "Character.h"
#include "EquipmentDb.h"
#include "Faction.h"
#include "ItemTypeFilterModel.h"
#include "Item.h"

ItemModel::ItemModel(EquipmentDb* db,
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
    this->current_sorting_method = ItemSorting::Methods::ByIlvl;

    this->sorting_methods.insert(ItemSorting::Methods::ByIlvl, true);
    this->sorting_methods.insert(ItemSorting::Methods::ByName, false);
    this->sorting_methods.insert(ItemSorting::Methods::ByPatch, false);
    this->sorting_methods.insert(ItemSorting::Methods::ByItemType, false);
}

bool name(Item* lhs, Item* rhs) {
    return lhs->get_name() < rhs->get_name();
}

bool ilvl(Item* lhs, Item* rhs) {
    auto lhs_ilvl = lhs->get_value("item_lvl");
    auto rhs_ilvl = rhs->get_value("item_lvl");

    return lhs_ilvl == rhs_ilvl ? name(lhs, rhs) : lhs_ilvl > rhs_ilvl;
}

bool patch(Item* lhs, Item* rhs) {
    auto lhs_patch = QVersionNumber::fromString(lhs->get_value("patch"));
    auto rhs_patch = QVersionNumber::fromString(rhs->get_value("patch"));

    return lhs_patch == rhs_patch ? ilvl(lhs, rhs) : lhs_patch > rhs_patch;
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

void ItemModel::set_patch(const QString &patch) {
    db->set_patch(patch);
    update_items();
}

void ItemModel::setSlot(const int slot) {
    this->slot = slot;
    update_items();
}

void ItemModel::selectSort(const int method) {
    layoutAboutToBeChanged();

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
    case ItemSorting::Methods::ByPatch:
        std::sort(items.begin(), items.end(), patch);
        select_new_method(ItemSorting::Methods::ByPatch);
        break;
    case ItemSorting::Methods::ByItemType:
        std::sort(items.begin(), items.end(), item_type);
        select_new_method(ItemSorting::Methods::ByItemType);
        break;
    }

    layoutChanged();
}

void ItemModel::select_new_method(const ItemSorting::Methods new_method) {
    if (sorting_methods[new_method])
        std::reverse(items.begin(), items.end());

    sorting_methods[new_method] = !sorting_methods[new_method];
    current_sorting_method = new_method;

    QHash<ItemSorting::Methods, bool>::iterator it = sorting_methods.begin();
    while (it != sorting_methods.end()) {
        if (it.key() != new_method) {
            sorting_methods[it.key()] = false;
        }
        ++it;
    }

    Q_EMIT sortingMethodChanged();
}


void ItemModel::update_items() {
    if (!items.empty()) {
        beginResetModel();
        items.clear();
        endResetModel();
    }

    QVector<Item*> tmp_items = db->get_slot_items(this->slot);

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    for (auto & tmp_item : tmp_items) {
        if (!tmp_item->available_for_faction(static_cast<AvailableFactions::Name>(pchar->get_faction()->get_faction())))
            continue;

        if (!tmp_item->available_for_class(pchar->get_name()))
            continue;

        if (!item_type_filter_model->get_item_type_valid(tmp_item->get_item_type()))
            continue;

        if (item_type_filter_model->get_filter_active(tmp_item->get_item_type()))
            continue;

        if (item_stat_filter_model->item_passes_active_stat_filters(tmp_item))
            items << tmp_item;
    }
    endInsertRows();

    layoutAboutToBeChanged();
    std::sort(items.begin(), items.end(), ilvl);
    layoutChanged();
}

int ItemModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return items.count();
}

QVariant ItemModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();

    const Item* item = items[index.row()];

    if (role == NameRole)
        return item->get_name();
    if (role == PatchRole)
        return item->get_value("patch");
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

    return QVariant();
}

QHash<int, QByteArray> ItemModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[PatchRole] = "patch";
    roles[SourceRole] = "source";
    roles[TypeRole] = "type";
    roles[ReqLvlRole] = "req_lvl";
    roles[ItemLvlRole] = "item_lvl";
    roles[QualityRole] = "quality";
    roles[IconRole] = "icon";
    return roles;
}
