#ifndef NUMBERCRUNCHER_H
#define NUMBERCRUNCHER_H

#include <QMap>
#include <QMutexLocker>
#include <QVector>
#include "SimSettings.h"

class BuffBreakdownModel;
class ClassStatistics;
class DebuffBreakdownModel;
class MeleeDamageBreakdownModel;
class MeleeDamageAvoidanceBreakdownModel;
class ProcBreakdownModel;
class ResourceBreakdownModel;
class StatisticsBuff;
class StatisticsProc;
class StatisticsResource;
class StatisticsSpell;


class NumberCruncher {
public:
    ~NumberCruncher();

    void add_class_statistic(SimOption, ClassStatistics*);
    void reset();

    double get_total_dps(SimOption) const;
    static double delta(double lhs, double rhs);
    void print();

private:
    friend class BuffBreakdownModel;
    friend class DebuffBreakdownModel;
    friend class MeleeDamageBreakdownModel;
    friend class MeleeDamageAvoidanceBreakdownModel;
    friend class ProcBreakdownModel;
    friend class ResourceBreakdownModel;

    QMutex mutex;
    QMap<SimOption, QVector<ClassStatistics*>> class_stats;

    double get_dps_for_option(SimOption) const;
    void calculate_stat_weights() const;

    void merge_spell_stats(QList<StatisticsSpell*>& vec);
    void merge_spell_entry(const QString& name, const QString &icon, long long int total_damage_dealt, QList<StatisticsSpell*>& vec);

    void merge_buff_stats(QList<StatisticsBuff*>& vec, const bool include_debuffs);
    void merge_buff_entry(const QString& name, const QString &icon, QList<StatisticsBuff*>& vec);

    void merge_proc_stats(QList<StatisticsProc*>& vec);
    void merge_proc_entry(const QString& name, const QString &icon, QList<StatisticsProc*>& vec);

    void merge_resource_stats(QList<StatisticsResource*>& vec);
    void merge_resource_entry(const QString& name, const QString &icon, QList<StatisticsResource*>& vec);
};

#endif // NUMBERCRUNCHER_H
