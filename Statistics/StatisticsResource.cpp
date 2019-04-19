#include "StatisticsResource.h"

#include <utility>

bool name(StatisticsResource* lhs, StatisticsResource* rhs) {
    return lhs->get_name() < rhs->get_name();
}

bool mana_gain(StatisticsResource* lhs, StatisticsResource* rhs) {
    return lhs->get_mana_gain_per_5() > rhs->get_mana_gain_per_5();
}

bool rage_gain(StatisticsResource* lhs, StatisticsResource* rhs) {
    return lhs->get_rage_gain_per_5() > rhs->get_rage_gain_per_5();
}

bool energy_gain(StatisticsResource* lhs, StatisticsResource* rhs) {
    return lhs->get_energy_gain_per_5() > rhs->get_energy_gain_per_5();
}

StatisticsResource::StatisticsResource(QString name, QString icon, const int time_in_combat) :
    name(std::move(name)),
    icon(std::move(icon)),
    time_in_combat(time_in_combat)
{}

void StatisticsResource::reset() {
    resource_gain.clear();
}

QString StatisticsResource::get_name() const {
    return this->name;
}

QString StatisticsResource::get_icon() const {
    return this->icon;
}

void StatisticsResource::add_resource_gain(const ResourceType resource, const unsigned gain) {
    if (!resource_gain.contains(resource))
        resource_gain[resource] = 0;

    resource_gain[resource] += gain;
}

double StatisticsResource::get_mana_gain_per_5() const {
   return static_cast<double>(resource_gain[ResourceType::Mana]) / time_in_combat * 5;
}

double StatisticsResource::get_rage_gain_per_5() const {
   return static_cast<double>(resource_gain[ResourceType::Rage]) / time_in_combat * 5;
}

double StatisticsResource::get_energy_gain_per_5() const {
   return static_cast<double>(resource_gain[ResourceType::Energy]) / time_in_combat * 5;
}

void StatisticsResource::add(const StatisticsResource* other) {
    QMap<ResourceType, unsigned>::const_iterator it = other->resource_gain.constBegin();
    auto end = other->resource_gain.constEnd();
    while (it != end) {
        if (!this->resource_gain.contains(it.key()))
            this->resource_gain[it.key()] = 0;

        this->resource_gain[it.key()] += it.value();

        ++it;
    }
}
