#pragma once

#include <QString>

class StatisticsBuff;

bool name(StatisticsBuff* lhs, StatisticsBuff* rhs);
bool min_uptime(StatisticsBuff* lhs, StatisticsBuff* rhs);
bool max_uptime(StatisticsBuff* lhs, StatisticsBuff* rhs);
bool avg_uptime(StatisticsBuff* lhs, StatisticsBuff* rhs);

class StatisticsBuff {
public:
    StatisticsBuff(QString  name, QString  icon, const bool debuff);

    void reset();

    QString get_name() const;
    QString get_icon() const;
    bool is_debuff() const;

    void add_uptime(const double);
    void add_uptime_for_encounter(const double);

    double get_min_uptime() const;
    double get_max_uptime() const;
    double get_avg_uptime() const;

    void add(const StatisticsBuff*);

private:
    const QString name;
    const QString icon;
    const bool debuff;
    double min_uptime;
    double max_uptime;
    double avg_uptime;
    int counter;

    bool min_uptime_set;
    bool max_uptime_set;

    void add_min_uptime(const double);
    void add_max_uptime(const double);
};
