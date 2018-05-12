
#include "StatisticsResource.h"

StatisticsResource::StatisticsResource(QString name) :
    name(name),
    resource_gain(0)
{}

void StatisticsResource::reset() {
    resource_gain = 0;
}

QString StatisticsResource::get_name() const {
    return this->name;
}

void StatisticsResource::add_resource_gain(const int gain) {
    resource_gain += gain;
}

int StatisticsResource::get_resource_gain() const {
   return resource_gain;
}
