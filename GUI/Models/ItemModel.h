#pragma once

#include <QAbstractListModel>
#include <QSet>
#include <QStringList>
#include <QVersionNumber>

#include "ContentPhase.h"

class ActiveItemStatFilterModel;
class Character;
class EquipmentDb;
class Item;
class ItemTypeFilterModel;

class ItemSorting : public QObject {
    Q_OBJECT
public:
    enum Methods
    {
        ByIlvl = 0,
        ByName,
        ByPhase,
        ByItemType
    };
    Q_ENUM(Methods)
};

class ItemModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum ItemRoles
    {
        IdRole = Qt::UserRole + 1,
        NameRole,
        PhaseRole,
        SourceRole,
        TypeRole,
        ReqLvlRole,
        ItemLvlRole,
        QualityRole,
        IconRole,
        RandomAffixRole
    };

    ItemModel(EquipmentDb*, ItemTypeFilterModel*, ActiveItemStatFilterModel*, QObject* parent = nullptr);

    void update_items();
    void set_character(Character* pchar);
    void set_phase(const Content::Phase phase);

    Q_INVOKABLE void setSlot(const int slot);
    Q_INVOKABLE void selectSort(const int method);
    Q_INVOKABLE void lexicalSearch(const QString& text);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

signals:
    void sortingMethodChanged();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    int slot;
    Character* pchar;
    EquipmentDb* db;
    ItemTypeFilterModel* item_type_filter_model;
    ActiveItemStatFilterModel* item_stat_filter_model;
    ItemSorting::Methods current_sorting_method;
    QHash<ItemSorting::Methods, bool> sorting_methods;
    QList<Item*> items;
    QSet<QString> lexical_search_terms;

    void select_new_method(const ItemSorting::Methods new_method);
    bool name_passes_lexical_search(const QString& name);
};
