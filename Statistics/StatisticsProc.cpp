
#include "StatisticsProc.h"

#include <utility>

StatisticsProc::StatisticsProc(QString name) :
    name(std::move(name)),
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

double StatisticsProc::get_proc_rate() const {
    return static_cast<double>(proc_counter) / static_cast<double>(attempts);
}
