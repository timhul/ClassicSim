#ifndef ITEMMODEL_H
#define ITEMMODEL_H

#include <QAbstractListModel>
#include <QStringList>

class Item;

class ItemModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ItemRoles {
        NameRole = Qt::UserRole + 1,
    };

    ItemModel(QObject *parent = 0);

    void addItem(Item *item);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<Item*> items;
};

#endif // ITEMMODEL_H
