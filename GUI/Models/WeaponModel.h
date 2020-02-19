#pragma once

#include <QAbstractListModel>
#include <QHash>
#include <QStringList>
#include <QVersionNumber>

#include "ContentPhase.h"

class ActiveItemStatFilterModel;
class Character;
class EquipmentDb;
class ItemTypeFilterModel;
class SortingMethod;
class Weapon;

class WeaponSorting : public QObject {
    Q_OBJECT
public:
    enum Methods
    {
        ByIlvl = 0,
        ByName,
        ByDps,
        BySpeed,
        ByPhase,
        ByItemType
    };
    Q_ENUMS(Methods)
};

class WeaponModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum WeaponRoles
    {
        IdRole = Qt::UserRole + 1,
        NameRole,
        SpeedRole,
        DpsRole,
        PhaseRole,
        SourceRole,
        TypeRole,
        ReqLvlRole,
        ItemLvlRole,
        QualityRole,
        IconRole,
        RandomAffixRole
    };

    WeaponModel(EquipmentDb*, ItemTypeFilterModel*, ActiveItemStatFilterModel*, QObject* parent = nullptr);

    void set_character(Character* pchar);
    void set_phase(const Content::Phase phase);
    Q_INVOKABLE void setSlot(const int slot);
    Q_INVOKABLE void selectSort(const int method);

    void update_items();

    int rowCount(const QModelIndex& = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    Q_PROPERTY(int currentSortingMethod READ get_current_sorting_method NOTIFY sortingMethodChanged)
    int get_current_sorting_method() const;

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
    QHash<WeaponSorting::Methods, bool> sorting_methods;
    QList<Weapon*> weapons;
    WeaponSorting::Methods current_sorting_method;

    void select_new_method(const WeaponSorting::Methods new_method);
};
