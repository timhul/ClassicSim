#ifndef STATISTICSPROC_H
#define STATISTICSPROC_H

#include <QString>

class StatisticsProc;

bool name(StatisticsProc* lhs, StatisticsProc* rhs);
bool avg_proc_rate(StatisticsProc* lhs, StatisticsProc* rhs);
bool num_procs(StatisticsProc* lhs, StatisticsProc* rhs);

class StatisticsProc {
public:
    StatisticsProc(const QString &name, const QString& icon);

    void reset();

    QString get_name() const;
    QString get_icon() const;
    int get_procs() const;
    int get_attempts() const;
    double get_avg_proc_rate() const;

    void increment_attempt();
    void increment_proc();

    void add(const StatisticsProc*);

protected:
private:
    const QString name;
    const QString icon;
    int attempts;
    int proc_counter;
};

#endif // STATISTICSPROC_H
