#ifndef AVAILABLEITEMSTATFILTERMODEL_H
#define AVAILABLEITEMSTATFILTERMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include "ItemStatsEnum.h"

class Character;
class Item;
class ActiveItemStatFilterModel;


class AvailableStatFilter {
public:
    explicit AvailableStatFilter(ItemStats item_stat_flag,
                                 const QString description) :
        item_stat_flag(item_stat_flag), description(description)
    {}

    ItemStats item_stat_flag;
    QString description;
};


class AvailableItemStatFilterModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum AvailableItemStatFilterRoles {
        IndexRole = Qt::UserRole + 1,
        DescriptionRole
    };

    AvailableItemStatFilterModel(ActiveItemStatFilterModel* active_stat_model, QObject *parent = nullptr);
    ~AvailableItemStatFilterModel();

    bool item_passes_active_stat_filters(const Item* item) const;

    Q_INVOKABLE void addStatFilter(int);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    ActiveItemStatFilterModel* active_stat_model;
    QVector<AvailableStatFilter*> available_item_stat_filters;

    void add_available_stat_filters();
};

#endif // AVAILABLEITEMSTATFILTERMODEL_H
