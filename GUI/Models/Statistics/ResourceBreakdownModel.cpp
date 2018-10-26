
#include "NumberCruncher.h"
#include "ResourceBreakdownModel.h"
#include "StatisticsResource.h"
#include <QDebug>

ResourceBreakdownModel::ResourceBreakdownModel(NumberCruncher *statistics_source, QObject *parent)
    : QAbstractListModel(parent),
      statistics_source(statistics_source)
{
    this->current_sorting_method = ResourceBreakdownSorting::Methods::ByRagePer5;
    this->sorting_methods.insert(ResourceBreakdownSorting::Methods::ByRagePer5, true);
    this->sorting_methods.insert(ResourceBreakdownSorting::Methods::ByName, false);
    this->sorting_methods.insert(ResourceBreakdownSorting::Methods::ByManaPer5, false);
    this->sorting_methods.insert(ResourceBreakdownSorting::Methods::ByEnergyPer5, false);
}

ResourceBreakdownModel::~ResourceBreakdownModel() {
    for (auto & i : resource_stats)
        delete i;
}

void ResourceBreakdownModel::selectSort(const int method) {
    layoutAboutToBeChanged();

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

    layoutChanged();
}

void ResourceBreakdownModel::select_new_method(const ResourceBreakdownSorting::Methods new_method) {
    if (sorting_methods[new_method])
        std::reverse(resource_stats.begin(), resource_stats.end());

    sorting_methods[new_method] = !sorting_methods[new_method];
    current_sorting_method = new_method;

    QHash<ResourceBreakdownSorting::Methods, bool>::iterator it = sorting_methods.begin();
    while (it != sorting_methods.end()) {
        if (it.key() != new_method) {
            sorting_methods[it.key()] = false;
        }
        ++it;
    }

    Q_EMIT sortingMethodChanged();
}

int ResourceBreakdownModel::get_current_sorting_method() const {
    return static_cast<int>(current_sorting_method);
}

void ResourceBreakdownModel::update_statistics() {
    if (!resource_stats.empty()) {
        beginRemoveRows(QModelIndex(), 0, resource_stats.size() - 1);

        for (auto & i : resource_stats)
            delete i;

        resource_stats.clear();
        endRemoveRows();
    }

    beginInsertRows(QModelIndex(), 0, rowCount());
    statistics_source->merge_resource_stats(resource_stats);
    endInsertRows();

    QList<StatisticsResource*>::iterator it = resource_stats.begin();
    while (it != resource_stats.end()) {
        unsigned resource_gains = (*it)->get_rage_gain() + (*it)->get_energy_gain() + (*it)->get_mana_gain();
        if (resource_gains == 0) {
            delete *it;
            it = resource_stats.erase(it);
        }
        else
            ++it;
    }

    layoutAboutToBeChanged();
    std::sort(resource_stats.begin(), resource_stats.end(), rage_gain);
    layoutChanged();
}

int ResourceBreakdownModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return resource_stats.count();
}

QVariant ResourceBreakdownModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= resource_stats.count())
        return QVariant();

    const StatisticsResource* resource_stat = resource_stats[index.row()];

    if (role == ResourceBreakdownSorting::ByName)
        return resource_stat->get_name();
    if (role == ResourceBreakdownSorting::Icon)
        return resource_stat->get_icon();
    if (role == ResourceBreakdownSorting::ByManaPer5)
        return resource_stat->get_mana_gain();
    if (role == ResourceBreakdownSorting::ByRagePer5)
        return resource_stat->get_rage_gain();
    if (role == ResourceBreakdownSorting::ByEnergyPer5)
        return resource_stat->get_energy_gain();

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
