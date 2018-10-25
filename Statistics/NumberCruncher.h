#ifndef NUMBERCRUNCHER_H
#define NUMBERCRUNCHER_H

#include <QMap>
#include <QMutexLocker>
#include <QVector>
#include "SimSettings.h"

class BuffBreakdownModel;
class ClassStatistics;
class MeleeDamageBreakdownModel;
class MeleeDamageAvoidanceBreakdownModel;
class StatisticsBuff;
class StatisticsSpell;


class NumberCruncher {
public:
    ~NumberCruncher();

    void add_class_statistic(SimOption, ClassStatistics*);
    void reset();

    static double delta(double lhs, double rhs);
    void print();

private:
    friend class BuffBreakdownModel;
    friend class MeleeDamageBreakdownModel;
    friend class MeleeDamageAvoidanceBreakdownModel;

    QMutex mutex;
    QMap<SimOption, QVector<ClassStatistics*>> class_stats;

    double get_dps_for_option(SimOption) const;
    void calculate_stat_weights() const;

    void merge_spell_stats(QList<StatisticsSpell*>& vec);
    void merge_spell_entry(const QString& name, const QString &icon, long long int total_damage_dealt, QList<StatisticsSpell*>& vec);

    void merge_buff_stats(QList<StatisticsBuff*>& vec);
    void merge_buff_entry(const QString& name, const QString &icon, QList<StatisticsBuff*>& vec);
};

#endif // NUMBERCRUNCHER_H
