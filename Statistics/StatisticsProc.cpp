
#include "StatisticsProc.h"

#include <utility>

bool name(StatisticsProc* lhs, StatisticsProc* rhs) {
    return lhs->get_name() < rhs->get_name();
}

bool avg_proc_rate(StatisticsProc* lhs, StatisticsProc* rhs) {
    auto lhs_proc_rate = lhs->get_avg_proc_rate();
    auto rhs_proc_rate = rhs->get_avg_proc_rate();

    return lhs_proc_rate > rhs_proc_rate;
}

bool num_procs(StatisticsProc* lhs, StatisticsProc* rhs) {
    auto lhs_procs = lhs->get_procs();
    auto rhs_procs = rhs->get_procs();

    return lhs_procs != rhs_procs ? lhs_procs > rhs_procs : name(lhs, rhs);
}

StatisticsProc::StatisticsProc(const QString& name, const QString &icon) :
    name(name),
    icon(icon),
    attempts(0),
    proc_counter(0)
{}

void StatisticsProc::reset() {
    attempts = 0;
    proc_counter = 0;
}

QString StatisticsProc::get_name() const {
    return this->name;
}

QString StatisticsProc::get_icon() const {
    return this->icon;
}

void StatisticsProc::increment_attempt() {
    ++attempts;
}

void StatisticsProc::increment_proc() {
    ++proc_counter;
}

int StatisticsProc::get_procs() const {
    return proc_counter;
}

int StatisticsProc::get_attempts() const {
    return attempts;
}

double StatisticsProc::get_avg_proc_rate() const {
    return static_cast<double>(proc_counter) / static_cast<double>(attempts);
}

void StatisticsProc::add(const StatisticsProc* other) {
    this->proc_counter += other->proc_counter;
    this->attempts += other->attempts;
}
