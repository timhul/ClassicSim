#ifndef STATISTICSBUFF_H
#define STATISTICSBUFF_H

#include <QString>

class StatisticsBuff {
public:
    StatisticsBuff(QString name);

    void reset();

    QString get_name() const;
    void add_uptime_for_encounter(const float);
    float get_uptime() const;

protected:
private:
    const QString name;
    float avg_uptime;
    int counter;
};

#endif // STATISTICSBUFF_H
