#include "StatisticsResource.h"

#include <utility>

bool name(StatisticsResource* lhs, StatisticsResource* rhs) {
    return lhs->get_name() < rhs->get_name();
}

bool mana_gain(StatisticsResource* lhs, StatisticsResource* rhs) {
    return lhs->get_mana_gain() > rhs->get_mana_gain();
}

bool rage_gain(StatisticsResource* lhs, StatisticsResource* rhs) {
    return lhs->get_rage_gain() > rhs->get_rage_gain();
}

bool energy_gain(StatisticsResource* lhs, StatisticsResource* rhs) {
    return lhs->get_energy_gain() > rhs->get_energy_gain();
}

StatisticsResource::StatisticsResource(QString  name, QString  icon) :
    name(std::move(name)),
    icon(std::move(icon))
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

unsigned StatisticsResource::get_mana_gain() const {
   return resource_gain[ResourceType::Mana];
}

unsigned StatisticsResource::get_rage_gain() const {
   return resource_gain[ResourceType::Rage];
}

unsigned StatisticsResource::get_energy_gain() const {
   return resource_gain[ResourceType::Energy];
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
