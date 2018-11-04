#ifndef NUMBERCRUNCHER_H
#define NUMBERCRUNCHER_H

#include <QMap>
#include <QMutexLocker>
#include <QVector>

#include "SimOption.h"
#include "SimSettings.h"

class BuffBreakdownModel;
class ClassStatistics;
class DebuffBreakdownModel;
class MeleeDamageBreakdownModel;
class MeleeDamageAvoidanceBreakdownModel;
class ProcBreakdownModel;
class ResourceBreakdownModel;
class ScaleResult;
class ScaleResultModel;
class StatisticsBuff;
class StatisticsProc;
class StatisticsResource;
class StatisticsSpell;

QString get_name_for_option(const SimOption::Name option);

class NumberCruncher {
public:
    ~NumberCruncher();

    void add_class_statistic(SimOption::Name, ClassStatistics*);
    void reset();

    double get_total_dps(SimOption::Name) const;
    static double delta(double lhs, double rhs);

private:
    friend class BuffBreakdownModel;
    friend class DebuffBreakdownModel;
    friend class MeleeDamageBreakdownModel;
    friend class MeleeDamageAvoidanceBreakdownModel;
    friend class ProcBreakdownModel;
    friend class ScaleResultModel;
    friend class ResourceBreakdownModel;

    QMutex mutex;
    QMap<SimOption::Name, QVector<ClassStatistics*>> class_stats;

    double get_dps_for_option(SimOption::Name) const;
    void calculate_stat_weights(QList<ScaleResult*>& list);

    void merge_spell_stats(QList<StatisticsSpell*>& vec);
    void merge_spell_entry(const QString& name, const QString &icon, long long int total_damage_dealt, QList<StatisticsSpell*>& vec);

    void merge_buff_stats(QList<StatisticsBuff*>& vec, const bool include_debuffs);
    void merge_buff_entry(const QString& name, const QString &icon, QList<StatisticsBuff*>& vec);

    void merge_proc_stats(QList<StatisticsProc*>& vec);
    void merge_proc_entry(const QString& name, const QString &icon, QList<StatisticsProc*>& vec);

    void merge_resource_stats(QList<StatisticsResource*>& vec);
    void merge_resource_entry(const QString& name, const QString &icon, QList<StatisticsResource*>& vec);
};

class ScaleResult {
public:
    ScaleResult(SimOption::Name option, double absolute_value, double relative_value) :
        option(option),
        absolute_value(absolute_value),
        relative_value(relative_value)
    {}

    const SimOption::Name option;
    const double absolute_value;
    const double relative_value;
};

#endif // NUMBERCRUNCHER_H
