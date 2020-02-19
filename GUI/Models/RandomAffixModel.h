#pragma once

#include <QAbstractListModel>
#include <QSet>

class EquipmentDb;
class RandomAffixes;

class RandomAffixModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum RandomAffixRoles
    {
        NameRole = Qt::UserRole + 1,
        DescriptionRole,
        IDRole
    };

    explicit RandomAffixModel(const int item_id, QObject* parent = nullptr);

    void set_equipment_db(EquipmentDb* equipment_db);
    void set_random_affixes_db(RandomAffixes* random_affixes);
    void set_id(const int item_id);
    void update_affixes();

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

private:
    EquipmentDb* equipment_db;
    RandomAffixes* random_affixes_db;
    int item_id;
    QVector<int> random_affixes;

    QHash<int, QByteArray> roleNames() const override;
};
