#pragma once

#include <QAbstractListModel>
#include <QStringList>

class Character;

class ItemTypeFilter {
public:
    explicit ItemTypeFilter(const int item_type, const QString name) : item_type(item_type), name(name), active(false) {}

    int item_type;
    QString name;
    bool active;
};

class ItemTypeFilterModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum ItemTypeFilterRoles
    {
        ItemTypeRole = Qt::UserRole + 1,
        DescriptionRole,
        ActiveRole
    };

    ItemTypeFilterModel(QObject* parent = nullptr);

    bool get_item_type_valid(const int item_type) const;
    bool get_filter_active(const int item_type) const;
    void toggle_single_filter(const int item_type);
    void clear_filters_and_select_single_filter(const int);
    void set_item_slot(const int equipment_slot);
    void select_range_of_filters(const int filter);

    void set_character(Character* pchar);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    Character* pchar;
    int equipment_slot {};
    int last_toggled;
    QVector<QList<ItemTypeFilter>> item_type_filters;

    void add_item_type_filters();
    void add_armor_item_type_filters();
    void add_weapon_item_type_filters();
};
