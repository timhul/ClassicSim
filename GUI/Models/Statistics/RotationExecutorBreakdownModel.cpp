#include "RotationExecutorBreakdownModel.h"

#include "NumberCruncher.h"
#include "RotationExecutorListModel.h"
#include "SortDirection.h"
#include "StatisticsRotationExecutor.h"

RotationExecutorBreakdownModel::RotationExecutorBreakdownModel(RotationExecutorListModel* data_source, QObject* parent) :
    QAbstractListModel(parent), data_source(data_source) {
    this->current_sorting_method = RotationExecutorBreakdownSorting::Methods::ByValue;
    this->sorting_methods.insert(RotationExecutorBreakdownSorting::Methods::ByExecutor, SortDirection::Forward);
    this->sorting_methods.insert(RotationExecutorBreakdownSorting::Methods::ByValue, SortDirection::Forward);
}

void RotationExecutorBreakdownModel::selectSort(const int method) {
    emit layoutAboutToBeChanged();

    auto sorting_method = static_cast<RotationExecutorBreakdownSorting::Methods>(method);
    switch (sorting_method) {
    case RotationExecutorBreakdownSorting::Methods::BySpellStatus:
    case RotationExecutorBreakdownSorting::Methods::ByExecutor:
        std::sort(data_source->executor_outcomes[executor_index].begin(), data_source->executor_outcomes[executor_index].end(), description);
        select_new_method(sorting_method);
        break;
    case RotationExecutorBreakdownSorting::Methods::ByValue:
        std::sort(data_source->executor_outcomes[executor_index].begin(), data_source->executor_outcomes[executor_index].end(), value);
        select_new_method(sorting_method);
        break;
    }

    emit layoutChanged();
}

void RotationExecutorBreakdownModel::set_index(const int index) {
    this->executor_index = index;
    update_statistics();
}

void RotationExecutorBreakdownModel::select_new_method(const RotationExecutorBreakdownSorting::Methods new_method) {
    if (sorting_methods[new_method] == SortDirection::Reverse)
        std::reverse(data_source->executor_outcomes[executor_index].begin(), data_source->executor_outcomes[executor_index].end());

    const auto next_sort_direction = sorting_methods[new_method] == SortDirection::Forward ? SortDirection::Reverse : SortDirection::Forward;
    current_sorting_method = new_method;

    for (auto& direction : sorting_methods)
        direction = SortDirection::Forward;

    sorting_methods[current_sorting_method] = next_sort_direction;

    emit sortingMethodChanged();
}

int RotationExecutorBreakdownModel::get_current_sorting_method() const {
    return static_cast<int>(current_sorting_method);
}

void RotationExecutorBreakdownModel::update_statistics() {
    beginResetModel();
    endResetModel();

    if (data_source->executor_outcomes.empty())
        return;

    emit layoutAboutToBeChanged();
    std::sort(data_source->executor_outcomes[executor_index].begin(), data_source->executor_outcomes[executor_index].end(), value);
    emit layoutChanged();
}

int RotationExecutorBreakdownModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return executor_index < data_source->executor_outcomes.size() ? data_source->executor_outcomes[executor_index].count() : 0;
}

QVariant RotationExecutorBreakdownModel::data(const QModelIndex& index, int role) const {
    if (data_source->executor_outcomes.size() <= executor_index || index.row() < 0
        || index.row() >= data_source->executor_outcomes[executor_index].count())
        return QVariant();

    ExecutorOutcome* outcome = data_source->executor_outcomes[executor_index][index.row()];

    if (role == RotationExecutorBreakdownSorting::ByExecutor)
        return StatisticsRotationExecutor::get_description_for_executor_result(outcome->result);
    if (role == RotationExecutorBreakdownSorting::BySpellStatus)
        return StatisticsRotationExecutor::get_description_for_status(outcome->spell_status);
    if (role == RotationExecutorBreakdownSorting::ByValue)
        return outcome->value;

    return QVariant();
}

QHash<int, QByteArray> RotationExecutorBreakdownModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[RotationExecutorBreakdownSorting::ByExecutor] = "_executor";
    roles[RotationExecutorBreakdownSorting::BySpellStatus] = "_spellstatus";
    roles[RotationExecutorBreakdownSorting::ByValue] = "_value";

    return roles;
}
