#ifndef STATISTICSPROC_H
#define STATISTICSPROC_H

#include <QString>

class StatisticsProc {
public:
    StatisticsProc(QString name);

    void reset();

    QString get_name() const;
    int get_procs() const;
    int get_attempts() const;
    float get_proc_rate() const;

    void increment_attempt();
    void increment_proc();

protected:
private:
    const QString name;
    int attempts;
    int proc_counter;
};

#endif // STATISTICSPROC_H
