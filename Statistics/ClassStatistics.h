#ifndef CLASSSTATISTICS_H
#define CLASSSTATISTICS_H

#include <QMap>
#include <QVariantList>
#include <QVector>

#include "SimOption.h"
#include "SimSettings.h"

class NumberCruncher;
class StatisticsBuff;
class StatisticsEngine;
class StatisticsProc;
class StatisticsResource;
class StatisticsRotationExecutor;
class StatisticsSpell;

class ClassStatistics {
public:
    ClassStatistics(SimSettings* settings, const bool ignore_non_buff_statistics = false);
    ~ClassStatistics();

    StatisticsSpell* get_spell_statistics(const QString& name, const QString &icon, const int spell_rank);
    StatisticsBuff* get_buff_statistics(const QString& name, const QString &icon, const bool debuff);
    StatisticsResource* get_resource_statistics(const QString& name, const QString& icon);
    StatisticsProc* get_proc_statistics(const QString& name, const QString &icon);
    StatisticsRotationExecutor* get_executor_statistics(const QString& name);
    StatisticsEngine* get_engine_statistics();
    int get_total_damage_dealt() const;
    double get_total_dps() const;

    void finish_combat_iteration();

    int get_total_damage_for_spell(const QString& name) const;

    void prepare_statistics();

    void set_sim_option(const SimOption::Name);

private:
    friend class NumberCruncher;

    SimSettings* sim_settings;
    SimOption::Name option;
    int combat_iterations;
    int combat_length;
    int damage_dealt_previous_iterations;
    const bool ignore_non_buff_statistics;

    StatisticsEngine* engine_statistics {nullptr};
    QMap<QString, StatisticsSpell*> spell_statistics;
    QMap<QString, StatisticsBuff*> buff_statistics;
    QMap<QString, StatisticsResource*> resource_statistics;
    QMap<QString, StatisticsProc*> proc_statistics;
    QList<StatisticsRotationExecutor*> rotation_executor_statistics;

    QVector<double> dps_for_iterations;

    void delete_objects();
};

#endif // CLASSSTATISTICS_H
