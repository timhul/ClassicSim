#pragma once

#include <QMap>
#include <QMutexLocker>
#include <QVector>

#include "RaidMemberResult.h"
#include "SimOption.h"
#include "SimSettings.h"

class BuffBreakdownModel;
class ClassStatistics;
class DebuffBreakdownModel;
class ExecutorOutcome;
class MeleeDamageAvoidanceBreakdownModel;
class MeleeDamageBreakdownModel;
class ProcBreakdownModel;
class ResourceBreakdownModel;
class ScaleResult;
class ScaleResultModel;
class StatisticsBuff;
class StatisticsEngine;
class StatisticsProc;
class StatisticsResource;
class StatisticsRotationExecutor;
class StatisticsSpell;
class ThreatBreakdownModel;

QString get_name_for_option(const SimOption::Name option);

class NumberCruncher {
public:
    ~NumberCruncher();

    void add_class_statistic(SimOption::Name, ClassStatistics*);
    void reset();

    double get_personal_dps(SimOption::Name) const;
    double get_personal_tps(SimOption::Name) const;
    double get_raid_dps() const;
    double get_raid_tps() const;

    ScaleResult* get_dps_distribution() const;

private:
    friend class BuffBreakdownModel;
    friend class DamageMetersModel;
    friend class DebuffBreakdownModel;
    friend class EngineBreakdownModel;
    friend class MeleeDamageAvoidanceBreakdownModel;
    friend class MeleeDamageBreakdownModel;
    friend class ProcBreakdownModel;
    friend class ResourceBreakdownModel;
    friend class RotationExecutorBreakdownModel;
    friend class RotationExecutorListModel;
    friend class ScaleResultModel;
    friend class ThreatBreakdownModel;

    int time_in_combat {0};
    int collected_iterations {0};

    QMutex mutex;
    QMap<SimOption::Name, QVector<ClassStatistics*>> class_stats;
    QVector<RaidMemberResult*> player_results;

    void merge_player_results(ClassStatistics*);

    double get_dps_for_option(SimOption::Name) const;
    double get_tps_for_option(SimOption::Name) const;
    QPair<double, double> get_min_max_dps_for_option(SimOption::Name) const;
    void calculate_stat_weights_for_dps(QList<ScaleResult*>& list);
    void calculate_stat_weights_for_tps(QList<ScaleResult*>& list);

    void merge_spell_stats(QList<StatisticsSpell*>& vec);
    void merge_spell_entry(const QString& name, const QString& icon, long long int total_damage_dealt, long long int total_threat_dealt, QList<StatisticsSpell*>& vec);

    void merge_buff_stats(QList<StatisticsBuff*>& vec, const bool include_debuffs);
    void merge_buff_entry(const QString& name, const QString& icon, QList<StatisticsBuff*>& vec);

    void merge_proc_stats(QList<StatisticsProc*>& vec);
    void merge_proc_entry(const QString& name, const QString& icon, QList<StatisticsProc*>& vec);

    void merge_resource_stats(QList<StatisticsResource*>& vec);
    void merge_resource_entry(const QString& name, const QString& icon, QList<StatisticsResource*>& vec);

    void merge_engine_stats(StatisticsEngine* statistics_engine);
    void merge_rotation_executor_stats(QList<QList<ExecutorOutcome*>>& list);

    double get_standard_deviation_for_option(SimOption::Name) const;
    double get_confidence_interval_for_option(SimOption::Name, const double) const;
};

class ScaleResult {
public:
    ScaleResult(SimOption::Name option,
                bool for_dps,
                double min_dps,
                double max_dps,
                double absolute_value,
                double relative_value,
                double standard_deviation,
                double confidence_interval) :
        option(option),
        for_dps(for_dps),
        min_dps(min_dps),
        max_dps(max_dps),
        absolute_value(absolute_value),
        relative_value(relative_value),
        standard_deviation(standard_deviation),
        confidence_interval(confidence_interval) {}

    const SimOption::Name option;
    const bool for_dps;
    const double min_dps;
    const double max_dps;
    const double absolute_value;
    const double relative_value;
    const double standard_deviation;
    const double confidence_interval;
};
