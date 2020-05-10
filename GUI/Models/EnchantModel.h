#pragma once

#include <QAbstractListModel>

#include "EnchantName.h"

class Character;

class EnchantModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum SimOptionRoles
    {
        NameRole = Qt::UserRole + 1,
        EffectRole,
        EnumRole
    };

    static const bool Permanent = true;
    static const bool Temporary = false;

    EnchantModel(const int equipment_slot, const bool permanent, QObject* parent = nullptr);

    void set_character(Character* pchar);
    void update_enchants();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

private:
    Character* pchar;
    EnchantInfo enchant_info;
    const int equipment_slot;
    const bool permanent;

    QHash<int, QByteArray> roleNames() const;
    QVector<EnchantName::Name> enchants;
};
