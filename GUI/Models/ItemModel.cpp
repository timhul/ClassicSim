
#include "ItemModel.h"
#include "Item.h"
#include "EquipmentDb.h"
#include <QDebug>

ItemModel::ItemModel(EquipmentDb* db, QObject *parent)
    : QAbstractListModel(parent)
{
    this->db = db;
    this->slot = ItemSlots::MAINHAND;
}

bool ilvl(Item* lhs, Item* rhs) {
    return lhs->get_value("item_lvl") > rhs->get_value("item_lvl");
}

void ItemModel::set_patch(const QString &patch) {
    db->set_patch(patch);
    addItems(this->db);
}

void ItemModel::setSlot(const int slot) {
    this->slot = slot;
    addItems(this->db);
}

void ItemModel::addItems(const EquipmentDb* db) {
    if (items.size() > 0) {
        beginRemoveRows(QModelIndex(), 0, items.size() - 1);
        items.clear();
        endRemoveRows();
    }

    QVector<Item*> tmp_items = db->get_slot_items(this->slot);

    for (int i = 0; i < tmp_items.size(); ++i) {
        addItem(tmp_items[i]);
    }

    layoutAboutToBeChanged();
    std::sort(items.begin(), items.end(), ilvl);
    layoutChanged();
}

void ItemModel::addItem(Item* item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    items << item;
    endInsertRows();
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
