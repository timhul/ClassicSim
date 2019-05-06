#include "EngineBreakdownModel.h"

#include "NumberCruncher.h"
#include "SortDirection.h"
#include "StatisticsEngine.h"

EngineBreakdownModel::EngineBreakdownModel(NumberCruncher *statistics_source, QObject *parent)
    : QAbstractListModel(parent),
      statistics_source(statistics_source),
      engine_stats(new StatisticsEngine())
{
    this->current_sorting_method = EngineBreakdownSorting::Methods::ByPercentage;
    this->sorting_methods.insert(EngineBreakdownSorting::Methods::ByEvent, SortDirection::Forward);
    this->sorting_methods.insert(EngineBreakdownSorting::Methods::ByPercentage, SortDirection::Forward);
    this->sorting_methods.insert(EngineBreakdownSorting::Methods::ByTotal, SortDirection::Forward);
    this->sorting_methods.insert(EngineBreakdownSorting::Methods::ByHandledPerMin, SortDirection::Forward);
}

EngineBreakdownModel::~EngineBreakdownModel() {
    delete engine_stats;
}

void EngineBreakdownModel::selectSort(const int method) {
    layoutAboutToBeChanged();

    auto sorting_method = static_cast<EngineBreakdownSorting::Methods>(method);
    switch (sorting_method) {
    case EngineBreakdownSorting::Methods::ByEvent:
        std::sort(event_statistics.begin(), event_statistics.end(), event_type);
        select_new_method(sorting_method);
        break;
    case EngineBreakdownSorting::Methods::ByPercentage:
    case EngineBreakdownSorting::Methods::ByTotal:
    case EngineBreakdownSorting::Methods::ByHandledPerMin:
        std::sort(event_statistics.begin(), event_statistics.end(), total);
        select_new_method(sorting_method);
        break;
    }

    layoutChanged();
}

void EngineBreakdownModel::select_new_method(const EngineBreakdownSorting::Methods new_method) {
    if (sorting_methods[new_method] == SortDirection::Reverse)
        std::reverse(event_statistics.begin(), event_statistics.end());

    const auto next_sort_direction = sorting_methods[new_method] == SortDirection::Forward ?
                SortDirection::Reverse: SortDirection::Forward;
    current_sorting_method = new_method;

    for (auto & direction : sorting_methods)
        direction = SortDirection::Forward;

    sorting_methods[current_sorting_method] = next_sort_direction;

    Q_EMIT sortingMethodChanged();
}

int EngineBreakdownModel::get_current_sorting_method() const {
    return static_cast<int>(current_sorting_method);
}

void EngineBreakdownModel::update_statistics() {
    if (!event_statistics.empty()) {
        beginResetModel();
        event_statistics.clear();
        delete engine_stats;
        engine_stats = new StatisticsEngine();
        endResetModel();
    }

    beginInsertRows(QModelIndex(), 0, rowCount());
    statistics_source->merge_engine_stats(engine_stats);
    endInsertRows();

    event_statistics = engine_stats->get_list_of_event_pairs();
    total_events = 0;
    for (const auto & event_pair : event_statistics)
        total_events += event_pair.second;

    time_in_combat = static_cast<unsigned>(statistics_source->time_in_combat);

    layoutAboutToBeChanged();
    std::sort(event_statistics.begin(), event_statistics.end(), total);
    layoutChanged();
}

double EngineBreakdownModel::events_handled_per_second() const {
    return static_cast<double>(total_events) / engine_stats->get_elapsed() * 1000;
}

int EngineBreakdownModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return event_statistics.count();
}

QVariant EngineBreakdownModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= event_statistics.count())
        return QVariant();

    QPair<Events, unsigned> event_to_num_handled = event_statistics[index.row()];

    if (role == EngineBreakdownSorting::ByEvent)
        return StatisticsEngine::get_name_for_event(event_to_num_handled.first);
    if (role == EngineBreakdownSorting::ByPercentage)
        return QString::number(static_cast<double>(event_to_num_handled.second) / total_events  * 100, 'f', 2);
    if (role == EngineBreakdownSorting::ByTotal)
        return event_to_num_handled.second;
    if (role == EngineBreakdownSorting::ByHandledPerMin)
        return QString::number(static_cast<double>(event_to_num_handled.second) / time_in_combat * 60, 'f', 1);

    return QVariant();
}

QHash<int, QByteArray> EngineBreakdownModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[EngineBreakdownSorting::ByEvent] = "_event";
    roles[EngineBreakdownSorting::ByPercentage] = "_percentage";
    roles[EngineBreakdownSorting::ByTotal] = "_total";
    roles[EngineBreakdownSorting::ByHandledPerMin] = "_permin";

    return roles;
}
