#include "ResourceBreakdownModel.h"

#include "NumberCruncher.h"
#include "SortDirection.h"
#include "StatisticsResource.h"
#include "Utils/CompareDouble.h"

ResourceBreakdownModel::ResourceBreakdownModel(NumberCruncher* statistics_source, QObject* parent) :
    QAbstractListModel(parent), statistics_source(statistics_source) {
    this->current_sorting_method = ResourceBreakdownSorting::Methods::ByRagePer5;
    this->sorting_methods.insert(ResourceBreakdownSorting::Methods::ByRagePer5, SortDirection::Forward);
    this->sorting_methods.insert(ResourceBreakdownSorting::Methods::ByName, SortDirection::Forward);
    this->sorting_methods.insert(ResourceBreakdownSorting::Methods::ByManaPer5, SortDirection::Forward);
    this->sorting_methods.insert(ResourceBreakdownSorting::Methods::ByEnergyPer5, SortDirection::Forward);
}

ResourceBreakdownModel::~ResourceBreakdownModel() {
    for (const auto& i : resource_stats)
        delete i;
}

void ResourceBreakdownModel::selectSort(const int method) {
    emit layoutAboutToBeChanged();

    auto sorting_method = static_cast<ResourceBreakdownSorting::Methods>(method);
    switch (sorting_method) {
    case ResourceBreakdownSorting::Methods::Icon:
    case ResourceBreakdownSorting::Methods::ByName:
        std::sort(resource_stats.begin(), resource_stats.end(), name);
        select_new_method(sorting_method);
        break;
    case ResourceBreakdownSorting::Methods::ByManaPer5:
        std::sort(resource_stats.begin(), resource_stats.end(), mana_gain);
        select_new_method(sorting_method);
        break;
    case ResourceBreakdownSorting::Methods::ByRagePer5:
        std::sort(resource_stats.begin(), resource_stats.end(), rage_gain);
        select_new_method(sorting_method);
        break;
    case ResourceBreakdownSorting::Methods::ByEnergyPer5:
        std::sort(resource_stats.begin(), resource_stats.end(), energy_gain);
        select_new_method(sorting_method);
        break;
    }

    emit layoutChanged();
}

void ResourceBreakdownModel::select_new_method(const ResourceBreakdownSorting::Methods new_method) {
    if (sorting_methods[new_method] == SortDirection::Reverse)
        std::reverse(resource_stats.begin(), resource_stats.end());

    const auto next_sort_direction = sorting_methods[new_method] == SortDirection::Forward ? SortDirection::Reverse : SortDirection::Forward;
    current_sorting_method = new_method;

    for (auto& direction : sorting_methods)
        direction = SortDirection::Forward;

    sorting_methods[current_sorting_method] = next_sort_direction;

    emit sortingMethodChanged();
}

int ResourceBreakdownModel::get_current_sorting_method() const {
    return static_cast<int>(current_sorting_method);
}

void ResourceBreakdownModel::update_statistics() {
    if (!resource_stats.empty()) {
        beginResetModel();

        for (const auto& i : resource_stats)
            delete i;

        resource_stats.clear();
        endResetModel();
    }

    beginInsertRows(QModelIndex(), 0, rowCount());
    statistics_source->merge_resource_stats(resource_stats);
    endInsertRows();

    QMap<ResourceType, double> resource_gains = {{ResourceType::Rage, 0.0}, {ResourceType::Mana, 0.0}, {ResourceType::Energy, 0.0}};
    QList<StatisticsResource*>::iterator it = resource_stats.begin();
    while (it != resource_stats.end()) {
        resource_gains[ResourceType::Rage] += (*it)->get_rage_gain_per_5();
        resource_gains[ResourceType::Mana] += (*it)->get_mana_gain_per_5();
        resource_gains[ResourceType::Energy] += (*it)->get_rage_gain_per_5();
        double resource_gains = (*it)->get_rage_gain_per_5() + (*it)->get_energy_gain_per_5() + (*it)->get_mana_gain_per_5();
        if (almost_equal(resource_gains, 0)) {
            delete *it;
            it = resource_stats.erase(it);
        } else
            ++it;
    }

    emit layoutAboutToBeChanged();
    if (resource_gains[ResourceType::Rage] > 0.01)
        std::sort(resource_stats.begin(), resource_stats.end(), rage_gain);
    else if (resource_gains[ResourceType::Mana] > 0.01)
        std::sort(resource_stats.begin(), resource_stats.end(), mana_gain);
    else if (resource_gains[ResourceType::Energy] > 0.01)
        std::sort(resource_stats.begin(), resource_stats.end(), energy_gain);
    emit layoutChanged();
}

int ResourceBreakdownModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return resource_stats.count();
}

QVariant ResourceBreakdownModel::data(const QModelIndex& index, int role) const {
    if (index.row() < 0 || index.row() >= resource_stats.count())
        return QVariant();

    const StatisticsResource* resource_stat = resource_stats[index.row()];

    if (role == ResourceBreakdownSorting::ByName)
        return resource_stat->get_name();
    if (role == ResourceBreakdownSorting::Icon)
        return resource_stat->get_icon();
    if (role == ResourceBreakdownSorting::ByManaPer5)
        return QString::number(resource_stat->get_mana_gain_per_5(), 'f', 2);
    if (role == ResourceBreakdownSorting::ByRagePer5)
        return QString::number(resource_stat->get_rage_gain_per_5(), 'f', 2);
    if (role == ResourceBreakdownSorting::ByEnergyPer5)
        return QString::number(resource_stat->get_energy_gain_per_5(), 'f', 2);

    return QVariant();
}

QHash<int, QByteArray> ResourceBreakdownModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[ResourceBreakdownSorting::ByName] = "_name";
    roles[ResourceBreakdownSorting::Icon] = "_icon";
    roles[ResourceBreakdownSorting::ByManaPer5] = "_mp5";
    roles[ResourceBreakdownSorting::ByRagePer5] = "_rp5";
    roles[ResourceBreakdownSorting::ByEnergyPer5] = "_ep5";

    return roles;
}
