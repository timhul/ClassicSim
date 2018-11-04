#ifndef CLASSSTATISTICS_H
#define CLASSSTATISTICS_H

#include <QVariantList>
#include <QMap>

#include "SimOption.h"
#include "SimSettings.h"

class NumberCruncher;
class StatisticsSpell;
class StatisticsBuff;
class StatisticsResource;
class StatisticsProc;

class ClassStatistics {
public:
    ClassStatistics(SimSettings* settings);
    virtual ~ClassStatistics();

    Q_INVOKABLE virtual int getNumStatisticsRows() const = 0;
    Q_INVOKABLE virtual QVariantList getTableInfo(const int index) const = 0;
    Q_INVOKABLE virtual QVariantList getChartInfo(const int index) const = 0;
    Q_INVOKABLE virtual QString getEntryIcon(const int index) const = 0;

    StatisticsSpell* get_spell_statistics(const QString& name, const QString &icon);
    StatisticsBuff* get_buff_statistics(const QString& name, const QString &icon, const bool debuff);
    StatisticsResource* get_resource_statistics(const QString& name, const QString& icon);
    StatisticsProc* get_proc_statistics(const QString& name, const QString &icon);
    int get_total_damage_dealt() const;
    double get_total_dps() const;

    int get_total_damage_for_spell(const QString& name) const;
    int get_total_attempts_for_spell(const QString& name) const;

    void prepare_statistics();

    void set_sim_option(const SimOption::Name);
    SimOption::Name get_sim_option() const;

protected:
    friend class NumberCruncher;

    SimSettings* sim_settings;
    SimOption::Name option;
    int combat_iterations;
    int combat_length;
    QMap<QString, StatisticsSpell*> spell_statistics;
    QMap<QString, StatisticsBuff*> buff_statistics;
    QMap<QString, StatisticsResource*> resource_statistics;
    QMap<QString, StatisticsProc*> proc_statistics;

    QVariantList get_damage_breakdown_table() const;
    QVariantList get_damage_breakdown_chart() const;

    QVariantList get_buff_uptime_table() const;
    virtual QVariantList get_resource_gain_table() const;
    QVariantList get_proc_table() const;

    void delete_maps();

};

#endif // CLASSSTATISTICS_H
