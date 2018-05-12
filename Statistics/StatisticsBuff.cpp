
#include "StatisticsBuff.h"

StatisticsBuff::StatisticsBuff(QString name) :
    name(name)
{}

void StatisticsBuff::reset() {
    counter = 0;
    avg_uptime = 0;
}

QString StatisticsBuff::get_name() const {
    return this->name;
}

void StatisticsBuff::add_uptime_for_encounter(const float uptime) {
    ++counter;
    avg_uptime = ((uptime) * (counter - 1) + avg_uptime) / counter;
}

float StatisticsBuff::get_uptime() const {
    return this->avg_uptime;
}
