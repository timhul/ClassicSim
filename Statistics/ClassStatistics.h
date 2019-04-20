#ifndef CLASSSTATISTICS_H
#define CLASSSTATISTICS_H

#include <QMap>
#include <QVariantList>
#include <QVector>

#include "SimOption.h"
#include "SimSettings.h"

class NumberCruncher;
class StatisticsSpell;
class StatisticsBuff;
class StatisticsEngine;
class StatisticsResource;
class StatisticsProc;

class ClassStatistics {
public:
    ClassStatistics(SimSettings* settings);
    ~ClassStatistics();

    StatisticsSpell* get_spell_statistics(const QString& name, const QString &icon);
    StatisticsBuff* get_buff_statistics(const QString& name, const QString &icon, const bool debuff);
    StatisticsResource* get_resource_statistics(const QString& name, const QString& icon);
    StatisticsProc* get_proc_statistics(const QString& name, const QString &icon);
    StatisticsEngine* get_engine_statistics();
    int get_total_damage_dealt() const;
    double get_total_dps() const;

    void finish_combat_iteration();

    int get_total_damage_for_spell(const QString& name) const;
    int get_total_attempts_for_spell(const QString& name) const;

    void prepare_statistics();

    void set_sim_option(const SimOption::Name);
    SimOption::Name get_sim_option() const;

private:
    friend class NumberCruncher;

    SimSettings* sim_settings;
    SimOption::Name option;
    int combat_iterations;
    int combat_length;
    int damage_dealt_previous_iterations;

    StatisticsEngine* engine_statistics {nullptr};
    QMap<QString, StatisticsSpell*> spell_statistics;
    QMap<QString, StatisticsBuff*> buff_statistics;
    QMap<QString, StatisticsResource*> resource_statistics;
    QMap<QString, StatisticsProc*> proc_statistics;

    QVector<double> dps_for_iterations;

    void delete_maps();
};

#endif // CLASSSTATISTICS_H
