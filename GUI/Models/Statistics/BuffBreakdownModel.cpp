
#include "NumberCruncher.h"
#include "BuffBreakdownModel.h"
#include "StatisticsBuff.h"
#include <QDebug>

BuffBreakdownModel::BuffBreakdownModel(NumberCruncher *statistics_source, QObject *parent)
    : QAbstractListModel(parent),
      statistics_source(statistics_source)
{
    this->current_sorting_method = BuffBreakdownSorting::Methods::ByAvgUptime;
    this->sorting_methods.insert(BuffBreakdownSorting::Methods::ByAvgUptime, true);
    this->sorting_methods.insert(BuffBreakdownSorting::Methods::ByName, false);
    this->sorting_methods.insert(BuffBreakdownSorting::Methods::ByMinUptime, false);
    this->sorting_methods.insert(BuffBreakdownSorting::Methods::ByMaxUptime, false);
}

BuffBreakdownModel::~BuffBreakdownModel() {
    for (auto & i : buff_stats)
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
    if (sorting_methods[new_method])
        std::reverse(buff_stats.begin(), buff_stats.end());

    sorting_methods[new_method] = !sorting_methods[new_method];
    current_sorting_method = new_method;

    QHash<BuffBreakdownSorting::Methods, bool>::iterator it = sorting_methods.begin();
    while (it != sorting_methods.end()) {
        if (it.key() != new_method) {
            sorting_methods[it.key()] = false;
        }
        ++it;
    }

    Q_EMIT sortingMethodChanged();
}

int BuffBreakdownModel::get_current_sorting_method() const {
    return static_cast<int>(current_sorting_method);
}

void BuffBreakdownModel::update_statistics() {
    if (!buff_stats.empty()) {
        beginResetModel();

        for (auto & i : buff_stats)
            delete i;

        buff_stats.clear();
        endResetModel();
    }

    beginInsertRows(QModelIndex(), 0, rowCount());
    statistics_source->merge_buff_stats(buff_stats);
    endInsertRows();

    layoutAboutToBeChanged();
    std::sort(buff_stats.begin(), buff_stats.end(), avg_uptime);
    layoutChanged();
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
