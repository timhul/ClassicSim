#pragma once

#include <QAbstractListModel>
#include <QMap>
#include <QStringList>

class Character;
class Rotation;

class RotationConditionsModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum RotationRoles
    {
        NameRole = Qt::UserRole + 1,
        IconRole,
        ConditionsRole,
    };

    RotationConditionsModel(QObject* parent = nullptr);

    void set_rotation(Rotation* rotation);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

private:
    Rotation* rotation {nullptr};
    QHash<int, QByteArray> roleNames() const;
};
