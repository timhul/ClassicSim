
#include "StatisticsProc.h"

StatisticsProc::StatisticsProc(QString name) :
    name(name),
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

float StatisticsProc::get_proc_rate() const {
    return (float)proc_counter / (float)attempts;
}
