#ifndef WEAPONMODEL_H
#define WEAPONMODEL_H

#include <QAbstractListModel>
#include <QStringList>

class Weapon;
class EquipmentDb;
class ItemTypeFilterModel;

class WeaponModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum WeaponRoles {
        NameRole = Qt::UserRole + 1,
        SpeedRole,
        DpsRole,
        PatchRole,
        SourceRole,
        TypeRole,
        ReqLvlRole,
        ItemLvlRole,
        QualityRole,
        IconRole
    };

    WeaponModel(EquipmentDb*, ItemTypeFilterModel*, QObject *parent = 0);

    void set_patch(const QString &patch);
    Q_INVOKABLE void setSlot(const int slot);

    void addWeapons(const EquipmentDb *db);
    void addWeapon(Weapon *weapon);

    void update_items();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    int slot;
    EquipmentDb* db;
    ItemTypeFilterModel* item_type_filter_model;
    QList<Weapon*> melee_weapons;
};

#endif // WEAPONMODEL_H
