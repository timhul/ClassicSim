#ifndef SIMSCALEMODEL_H
#define SIMSCALEMODEL_H

#include <QAbstractListModel>
#include <QStringList>

#include "SimOption.h"

class SimSettings;

class SimScaleModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum SimOptionRoles {
        NameRole = Qt::UserRole + 1,
        ActiveRole,
        EnumRole
    };

    SimScaleModel(SimSettings* sim_settings, QObject *parent = nullptr);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE void toggleOption(const int option);

private:
    QHash<int, QByteArray> roleNames() const;

    SimSettings* sim_settings;
    QList<SimOption::Name> sim_options;

    QString get_name_for_option(const SimOption::Name option) const;
};

#endif // SIMSCALEMODEL_H
