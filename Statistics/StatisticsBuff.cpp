#include "StatisticsBuff.h"

#include <utility>

bool name(StatisticsBuff* lhs, StatisticsBuff* rhs) {
    return lhs->get_name() < rhs->get_name();
}

bool min_uptime(StatisticsBuff* lhs, StatisticsBuff* rhs) {
    auto lhs_uptime = lhs->get_min_uptime();
    auto rhs_uptime = rhs->get_min_uptime();

    return lhs_uptime > rhs_uptime;
}

bool max_uptime(StatisticsBuff* lhs, StatisticsBuff* rhs) {
    auto lhs_uptime = lhs->get_max_uptime();
    auto rhs_uptime = rhs->get_max_uptime();

    return lhs_uptime > rhs_uptime;
}

bool avg_uptime(StatisticsBuff* lhs, StatisticsBuff* rhs) {
    auto lhs_uptime = lhs->get_avg_uptime();
    auto rhs_uptime = rhs->get_avg_uptime();

    return lhs_uptime > rhs_uptime;
}

StatisticsBuff::StatisticsBuff(QString name, QString icon, const bool debuff) :
    name(std::move(name)),
    icon(std::move(icon)),
    debuff(debuff),
    min_uptime(std::numeric_limits<double>::max()),
    max_uptime(std::numeric_limits<double>::min()),
    avg_uptime(0),
    counter(0),
    min_uptime_set(false),
    max_uptime_set(false) {}

void StatisticsBuff::reset() {
    counter = 0;
    avg_uptime = 0;
}

QString StatisticsBuff::get_name() const {
    return this->name;
}

QString StatisticsBuff::get_icon() const {
    return this->icon;
}

bool StatisticsBuff::is_debuff() const {
    return this->debuff;
}

void StatisticsBuff::add_uptime(const double uptime) {
    add_min_uptime(uptime);
    add_max_uptime(uptime);
}

void StatisticsBuff::add_uptime_for_encounter(const double uptime) {
    ++counter;
    avg_uptime = avg_uptime + (uptime - avg_uptime) / counter;
}

double StatisticsBuff::get_min_uptime() const {
    return min_uptime_set ? this->min_uptime : 0.0;
}

double StatisticsBuff::get_max_uptime() const {
    return max_uptime_set ? this->max_uptime : 0.0;
}

double StatisticsBuff::get_avg_uptime() const {
    return this->avg_uptime;
}

void StatisticsBuff::add(const StatisticsBuff* other) {
    if (other->min_uptime < this->min_uptime)
        this->min_uptime = other->min_uptime;
    this->min_uptime_set = this->min_uptime_set ? true : other->min_uptime_set;

    if (other->max_uptime > this->max_uptime)
        this->max_uptime = other->max_uptime;
    this->max_uptime_set = this->max_uptime_set ? true : other->max_uptime_set;

    int total_counter = this->counter + other->counter;
    this->avg_uptime = this->avg_uptime * (double(this->counter) / total_counter) + other->avg_uptime * (double(other->counter) / total_counter);
    this->counter += other->counter;
}

void StatisticsBuff::add_min_uptime(const double uptime) {
    if (uptime < min_uptime) {
        min_uptime = uptime;
        min_uptime_set = true;
    }
}

void StatisticsBuff::add_max_uptime(const double uptime) {
    if (uptime > max_uptime) {
        max_uptime = uptime;
        max_uptime_set = true;
    }
}
