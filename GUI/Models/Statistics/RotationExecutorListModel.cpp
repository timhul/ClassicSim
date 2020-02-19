#include "RotationExecutorListModel.h"

#include "NumberCruncher.h"
#include "RotationExecutorBreakdownModel.h"
#include "SortDirection.h"
#include "StatisticsRotationExecutor.h"

RotationExecutorListModel::RotationExecutorListModel(NumberCruncher* statistics_source, QObject* parent) :
    QAbstractListModel(parent), executor_breakdown_model(new RotationExecutorBreakdownModel(this)), statistics_source(statistics_source) {}

RotationExecutorListModel::~RotationExecutorListModel() {
    delete executor_breakdown_model;
    delete_list();
}

void RotationExecutorListModel::selectExecutor(const int executor_index) {
    if (executor_outcomes.size() <= executor_index)
        return;

    beginResetModel();
    this->executor_index = executor_index;
    endResetModel();

    executor_breakdown_model->set_index(executor_index);
}

void RotationExecutorListModel::delete_list() {
    for (const auto& list : executor_outcomes)
        for (const auto& outcome : list)
            delete outcome;

    executor_outcomes.clear();
}

void RotationExecutorListModel::update_statistics() {
    if (!executor_outcomes.empty()) {
        beginResetModel();
        delete_list();
        endResetModel();
        executor_index = 0;
    }

    beginInsertRows(QModelIndex(), 0, rowCount());
    statistics_source->merge_rotation_executor_stats(executor_outcomes);
    endInsertRows();

    if (executor_outcomes.empty())
        return executor_breakdown_model->update_statistics();

    emit layoutAboutToBeChanged();
    std::sort(executor_outcomes[executor_index].begin(), executor_outcomes[executor_index].end(), value);
    emit layoutChanged();

    executor_breakdown_model->update_statistics();
}

int RotationExecutorListModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return executor_outcomes.count();
}

QVariant RotationExecutorListModel::data(const QModelIndex& index, int role) const {
    if (executor_outcomes.size() <= executor_index || index.row() < 0)
        return QVariant();

    if (role == RotationExecutorListRoles::Name)
        return executor_outcomes[index.row()][0]->name;
    if (role == RotationExecutorListRoles::Index)
        return index.row();
    if (role == RotationExecutorListRoles::Selected)
        return executor_index == index.row();

    return QVariant();
}

QHash<int, QByteArray> RotationExecutorListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[RotationExecutorListRoles::Name] = "_name";
    roles[RotationExecutorListRoles::Index] = "_index";
    roles[RotationExecutorListRoles::Selected] = "_selected";

    return roles;
}
