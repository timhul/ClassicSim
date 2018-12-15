#ifndef ENCHANTMODEL_H
#define ENCHANTMODEL_H

#include <QAbstractListModel>

#include "EnchantName.h"

class Character;

class EnchantModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum SimOptionRoles {
        NameRole = Qt::UserRole + 1,
        EffectRole,
        EnumRole
    };

    static const bool Permanent = true;
    static const bool Temporary = false;

    EnchantModel(const int equipment_slot, const bool permanent, QObject *parent = nullptr);

    void set_character(Character*);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

private:
    const int equipment_slot;
    const bool permanent;
    QHash<int, QByteArray> roleNames() const;
    QVector<EnchantName::Name> enchants;
};

#endif // ENCHANTMODEL_H
