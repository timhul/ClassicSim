#ifndef ITEMSTATFILTERMODEL_H
#define ITEMSTATFILTERMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include "ItemStatsEnum.h"

class Character;
class Item;
class ItemModel;
class WeaponModel;


namespace StatComparator {
    static const unsigned Less = 0;
    static const unsigned LEQ = 1;
    static const unsigned Equal = 2;
    static const unsigned Greater = 3;
    static const unsigned GEQ = 4;
};

class ItemStatFilter
{
public:
    explicit ItemStatFilter(ItemStats item_stat_flag,
                            const QString description) :
        item_stat_flag(item_stat_flag), description(description), comparator(StatComparator::Greater), cmp_value(0)
    {}

    bool item_passes_filter(const Item*) const;

    ItemStats item_stat_flag;
    QString description;
    unsigned comparator;
    unsigned cmp_value;

    QString get_comparator_string() const;
};


class ActiveItemStatFilterModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ActiveItemStatFilterRoles {
        ItemStatRole = Qt::UserRole + 1,
        DescriptionRole,
        ComparatorRole,
        CompareValueRole
    };

    ActiveItemStatFilterModel(QObject *parent = nullptr);
    ~ActiveItemStatFilterModel();

    bool item_passes_active_stat_filters(const Item* item) const;

    void set_item_model(ItemModel*);
    void set_weapon_model(WeaponModel*);

    void add_filter(const ItemStats, const QString&);
    Q_INVOKABLE void removeFilter(const int);
    Q_INVOKABLE void clearFilters();
    Q_INVOKABLE void changeComparator(const unsigned item_stat_flag_unsigned, const unsigned comparator);
    Q_INVOKABLE void changeCompareValue(const unsigned item_stat_flag_unsigned, const unsigned cmp_value);

    Q_INVOKABLE

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    ItemModel* item_model;
    WeaponModel* weapon_model;
    QVector<ItemStatFilter*> active_item_stat_filters;

    void update_affected_models();
};


#endif // ITEMSTATFILTERMODEL_H
