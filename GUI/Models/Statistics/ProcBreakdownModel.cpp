
#include "NumberCruncher.h"
#include "ProcBreakdownModel.h"
#include "StatisticsProc.h"
#include <QDebug>

ProcBreakdownModel::ProcBreakdownModel(NumberCruncher *statistics_source, QObject *parent)
    : QAbstractListModel(parent),
      statistics_source(statistics_source)
{
    this->current_sorting_method = ProcBreakdownSorting::Methods::ByAvgProcRate;
    this->sorting_methods.insert(ProcBreakdownSorting::Methods::ByAvgProcRate, true);
    this->sorting_methods.insert(ProcBreakdownSorting::Methods::ByName, false);
    this->sorting_methods.insert(ProcBreakdownSorting::Methods::ByNumProcs, false);
}

ProcBreakdownModel::~ProcBreakdownModel() {
    for (auto & i : proc_stats)
        delete i;
}

void ProcBreakdownModel::selectSort(const int method) {
    layoutAboutToBeChanged();

    auto sorting_method = static_cast<ProcBreakdownSorting::Methods>(method);
    switch (sorting_method) {
    case ProcBreakdownSorting::Methods::Icon:
    case ProcBreakdownSorting::Methods::ByName:
        std::sort(proc_stats.begin(), proc_stats.end(), name);
        select_new_method(sorting_method);
        break;
    case ProcBreakdownSorting::Methods::ByAvgProcRate:
        std::sort(proc_stats.begin(), proc_stats.end(), avg_proc_rate);
        select_new_method(sorting_method);
        break;
    case ProcBreakdownSorting::Methods::ByNumProcs:
        std::sort(proc_stats.begin(), proc_stats.end(), num_procs);
        select_new_method(sorting_method);
        break;
    }

    layoutChanged();
}

void ProcBreakdownModel::select_new_method(const ProcBreakdownSorting::Methods new_method) {
    if (sorting_methods[new_method])
        std::reverse(proc_stats.begin(), proc_stats.end());

    sorting_methods[new_method] = !sorting_methods[new_method];
    current_sorting_method = new_method;

    QHash<ProcBreakdownSorting::Methods, bool>::iterator it = sorting_methods.begin();
    while (it != sorting_methods.end()) {
        if (it.key() != new_method) {
            sorting_methods[it.key()] = false;
        }
        ++it;
    }

    Q_EMIT sortingMethodChanged();
}

int ProcBreakdownModel::get_current_sorting_method() const {
    return static_cast<int>(current_sorting_method);
}

void ProcBreakdownModel::update_statistics() {
    if (!proc_stats.empty()) {
        beginRemoveRows(QModelIndex(), 0, proc_stats.size() - 1);

        for (auto & i : proc_stats)
            delete i;

        proc_stats.clear();
        endRemoveRows();
    }

    beginInsertRows(QModelIndex(), 0, rowCount());
    statistics_source->merge_proc_stats(proc_stats);
    endInsertRows();

    layoutAboutToBeChanged();
    std::sort(proc_stats.begin(), proc_stats.end(), avg_proc_rate);
    layoutChanged();
}

int ProcBreakdownModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return proc_stats.count();
}

QVariant ProcBreakdownModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= proc_stats.count())
        return QVariant();

    const StatisticsProc* proc_stat = proc_stats[index.row()];

    if (role == ProcBreakdownSorting::ByName)
        return proc_stat->get_name();
    if (role == ProcBreakdownSorting::Icon)
        return proc_stat->get_icon();
    if (role == ProcBreakdownSorting::ByAvgProcRate)
        return QString::number(proc_stat->get_avg_proc_rate() * 100, 'f', 2);
    if (role == ProcBreakdownSorting::ByNumProcs)
        return proc_stat->get_procs();

    return QVariant();
}

QHash<int, QByteArray> ProcBreakdownModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[ProcBreakdownSorting::ByName] = "_name";
    roles[ProcBreakdownSorting::Icon] = "_icon";
    roles[ProcBreakdownSorting::ByAvgProcRate] = "_avgprocrate";
    roles[ProcBreakdownSorting::ByNumProcs] = "_numprocs";

    return roles;
}
