#include "BuffBreakdownModel.h"

#include "NumberCruncher.h"
#include "SortDirection.h"
#include "StatisticsBuff.h"

BuffBreakdownModel::BuffBreakdownModel(NumberCruncher *statistics_source, QObject *parent)
    : QAbstractListModel(parent),
      statistics_source(statistics_source)
{
    this->current_sorting_method = BuffBreakdownSorting::Methods::ByAvgUptime;
    this->sorting_methods.insert(BuffBreakdownSorting::Methods::ByAvgUptime, SortDirection::Forward);
    this->sorting_methods.insert(BuffBreakdownSorting::Methods::ByName, SortDirection::Forward);
    this->sorting_methods.insert(BuffBreakdownSorting::Methods::ByMinUptime, SortDirection::Forward);
    this->sorting_methods.insert(BuffBreakdownSorting::Methods::ByMaxUptime, SortDirection::Forward);
}

BuffBreakdownModel::~BuffBreakdownModel() {
    for (const auto & i : buff_stats)
        delete i;
}

void BuffBreakdownModel::selectSort(const int method) {
    layoutAboutToBeChanged();

    auto sorting_method = static_cast<BuffBreakdownSorting::Methods>(method);
    switch (sorting_method) {
    case BuffBreakdownSorting::Methods::Icon:
    case BuffBreakdownSorting::Methods::ByName:
        std::sort(buff_stats.begin(), buff_stats.end(), name);
        select_new_method(sorting_method);
        break;
    case BuffBreakdownSorting::Methods::ByAvgUptime:
        std::sort(buff_stats.begin(), buff_stats.end(), avg_uptime);
        select_new_method(sorting_method);
        break;
    case BuffBreakdownSorting::Methods::ByMinUptime:
        std::sort(buff_stats.begin(), buff_stats.end(), min_uptime);
        select_new_method(sorting_method);
        break;
    case BuffBreakdownSorting::Methods::ByMaxUptime:
        std::sort(buff_stats.begin(), buff_stats.end(), max_uptime);
        select_new_method(sorting_method);
        break;
    }

    layoutChanged();
}

void BuffBreakdownModel::select_new_method(const BuffBreakdownSorting::Methods new_method) {
    if (sorting_methods[new_method] == SortDirection::Reverse)
        std::reverse(buff_stats.begin(), buff_stats.end());

    const auto next_sort_direction = sorting_methods[new_method] == SortDirection::Forward ?
                SortDirection::Reverse: SortDirection::Forward;
    current_sorting_method = new_method;

    for (auto & direction : sorting_methods)
        direction = SortDirection::Forward;

    sorting_methods[current_sorting_method] = next_sort_direction;

    Q_EMIT sortingMethodChanged();
}

int BuffBreakdownModel::get_current_sorting_method() const {
    return static_cast<int>(current_sorting_method);
}

void BuffBreakdownModel::update_statistics() {
    if (!buff_stats.empty()) {
        beginResetModel();

        for (const auto & i : buff_stats)
            delete i;

        buff_stats.clear();
        endResetModel();
    }

    beginInsertRows(QModelIndex(), 0, rowCount());
    add_statistics();
    endInsertRows();

    layoutAboutToBeChanged();
    std::sort(buff_stats.begin(), buff_stats.end(), avg_uptime);
    layoutChanged();
}

void BuffBreakdownModel::add_statistics() {
    statistics_source->merge_buff_stats(buff_stats, false);
}

int BuffBreakdownModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return buff_stats.count();
}

QVariant BuffBreakdownModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= buff_stats.count())
        return QVariant();

    const StatisticsBuff* buff_stat = buff_stats[index.row()];

    if (role == BuffBreakdownSorting::ByName)
        return buff_stat->get_name();
    if (role == BuffBreakdownSorting::Icon)
        return buff_stat->get_icon();
    if (role == BuffBreakdownSorting::ByAvgUptime)
        return QString::number(buff_stat->get_avg_uptime() * 100, 'f', 2);
    if (role == BuffBreakdownSorting::ByMinUptime)
        return QString::number(buff_stat->get_min_uptime(), 'f', 1);
    if (role == BuffBreakdownSorting::ByMaxUptime)
        return QString::number(buff_stat->get_max_uptime(), 'f', 1);

    return QVariant();
}

QHash<int, QByteArray> BuffBreakdownModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[BuffBreakdownSorting::ByName] = "_name";
    roles[BuffBreakdownSorting::Icon] = "_icon";
    roles[BuffBreakdownSorting::ByAvgUptime] = "_avguptime";
    roles[BuffBreakdownSorting::ByMinUptime] = "_minuptime";
    roles[BuffBreakdownSorting::ByMaxUptime] = "_maxuptime";

    return roles;
}
