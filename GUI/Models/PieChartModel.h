#ifndef PIEMODEL_H
#define PIEMODEL_H

#include <QAbstractItemModel>

class PieChartModel : public QAbstractItemModel {
    Q_OBJECT

public:
    PieChartModel();

    enum SliceRoles {
        LabelRole = Qt::UserRole + 1,
        ValueRole
    };

    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QModelIndex parent(const QModelIndex &child) const override;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

    void updateLabels();

private:
    QVector<QPair<QString, double>> slices;
};

#endif // PIEMODEL_H
