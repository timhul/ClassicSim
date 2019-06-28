#pragma once

#include <QString>

class StatisticsProc;

bool name(StatisticsProc* lhs, StatisticsProc* rhs);
bool avg_proc_rate(StatisticsProc* lhs, StatisticsProc* rhs);
bool num_procs(StatisticsProc* lhs, StatisticsProc* rhs);

class StatisticsProc {
public:
    StatisticsProc(QString name, QString icon, const int time_in_combat);

    void reset();

    QString get_name() const;
    QString get_icon() const;
    int get_procs() const;
    int get_attempts() const;
    double get_avg_proc_rate() const;
    double get_effective_ppm() const;

    void increment_attempt();
    void increment_proc();

    void add(const StatisticsProc*);

private:
    const QString name;
    const QString icon;
    const int time_in_combat;
    int attempts {0};
    int proc_counter {0};
};
