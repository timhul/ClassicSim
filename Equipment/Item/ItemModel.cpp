
#include "ItemModel.h"
#include "Item.h"

ItemModel::ItemModel(QObject *parent)
    : QAbstractListModel(parent)
{}

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

    return QVariant();
}

QHash<int, QByteArray> ItemModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    return roles;
}
