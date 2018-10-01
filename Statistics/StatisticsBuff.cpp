
#include "StatisticsBuff.h"

#include <utility>

StatisticsBuff::StatisticsBuff(QString name) :
    name(std::move(name))
{
    reset();
}

void StatisticsBuff::reset() {
    counter = 0;
    avg_uptime = 0;
}

QString StatisticsBuff::get_name() const {
    return this->name;
}

void StatisticsBuff::add_uptime_for_encounter(const double uptime) {
    ++counter;
    avg_uptime = counter == 1 ? uptime : ((uptime) * (counter - 1) + avg_uptime) / counter;
}

double StatisticsBuff::get_uptime() const {
    return this->avg_uptime;
}
