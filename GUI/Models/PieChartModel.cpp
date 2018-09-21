
#include "PieChartModel.h"
#include <QDebug>

PieChartModel::PieChartModel()
{
    slices.append(QPair<QString, double>("Jane", 1));
    slices.append(QPair<QString, double>("Joe", 2));

    updateLabels();
}

int PieChartModel::rowCount(const QModelIndex &) const {
    return slices.size();
}

int PieChartModel::columnCount(const QModelIndex &) const {
    // Label + value
    return 2;
}

QVariant PieChartModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= slices.count() || index.column() > 1)
        return QVariant();

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            return QVariant(slices[index.row()].first);
        case 1:
            return QVariant(slices[index.row()].second);
        }
    }

    return QVariant();
}

QModelIndex PieChartModel::index(int row, int column, const QModelIndex &) const {
    if (row >= slices.size() || column > 1)
        return QModelIndex();

    return createIndex(row, column);
}

QModelIndex PieChartModel::parent(const QModelIndex &) const {
    return QModelIndex();
}

void PieChartModel::updateLabels() {
    double total = 0;
    for (int i = 0; i < slices.size(); ++i) {
        total += slices[i].second;
    }

    for (int i = 0; i < slices.size(); ++i) {
        QString label = slices[i].first;
        QString number = QString::number(slices[i].second / total * 100, 'f', 2);

        slices[i].first = QString("%1 %2%").arg(label, number);
    }
}
