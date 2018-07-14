#ifndef ITEMMODEL_H
#define ITEMMODEL_H

#include <QAbstractListModel>
#include <QStringList>

class Item;
class EquipmentDb;
class ItemTypeFilterModel;

class ItemModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ItemRoles {
        NameRole = Qt::UserRole + 1,
        PatchRole,
        SourceRole,
        TypeRole,
        ReqLvlRole,
        ItemLvlRole,
        QualityRole,
        IconRole
    };

    ItemModel(EquipmentDb*, ItemTypeFilterModel*, QObject *parent = 0);

    void set_patch(const QString &patch);
    Q_INVOKABLE void setSlot(const int slot);

    void addItems(const EquipmentDb *db);
    void addItem(Item* item);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    int slot;
    EquipmentDb* db;
    ItemTypeFilterModel* item_type_filter_model;
    QList<Item*> items;
};

#endif // ITEMMODEL_H
