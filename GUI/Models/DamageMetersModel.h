#pragma once

#include <QAbstractListModel>
#include <QVector>

#include "RaidMemberResult.h"

class NumberCruncher;

class DamageMetersModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum DamageRoles
    {
        NameRole = Qt::UserRole + 1,
        DpsRole,
        DpsRatioRole,
        DpsRatioStringRole,
        ClassColor,
        PlaceRole,
    };

    DamageMetersModel(NumberCruncher* statistics_source, QObject* parent = nullptr);
    ~DamageMetersModel();

    void update_statistics();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
    NumberCruncher* statistics_source;
    QList<RaidMemberResult*> player_results;

    double max_recorded_dps {1.0};

    void add_statistics();
};
