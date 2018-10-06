#ifndef CLASSSTATISTICS_H
#define CLASSSTATISTICS_H

#include <QObject>
#include <QVariantList>
#include <QMap>

class StatisticsSpell;
class StatisticsBuff;
class StatisticsResource;
class StatisticsProc;

class ClassStatistics : public QObject {
    Q_OBJECT

public:
    ClassStatistics(QObject* parent = nullptr);

    Q_INVOKABLE virtual int getNumStatisticsRows() const = 0;
    Q_INVOKABLE virtual QVariantList getTableInfo(const int index) const = 0;
    Q_INVOKABLE virtual QVariantList getChartInfo(const int index) const = 0;
    Q_INVOKABLE virtual QString getEntryIcon(const int index) const = 0;

    void add_spell_statistics(StatisticsSpell *);
    void add_buff_statistics(StatisticsBuff *);
    void add_resource_statistics(StatisticsResource*);
    void add_proc_statistics(StatisticsProc*);
    int get_total_damage_dealt() const;

    void remove_spell_statistics(const QString& key);
    void remove_buff_statistics(const QString& key);
    void remove_resource_statistics(const QString& key);
    void remove_proc_statistics(const QString& key);

    int get_total_damage_for_spell(const QString& name) const;
    int get_total_attempts_for_spell(const QString& name) const;

    void reset_statistics();

protected:
    QMap<QString, StatisticsSpell*> spell_statistics;
    QMap<QString, StatisticsBuff*> buff_statistics;
    QMap<QString, StatisticsResource*> resource_statistics;
    QMap<QString, StatisticsProc*> proc_statistics;

    QVariantList get_damage_breakdown_table() const;
    QVariantList get_damage_breakdown_chart() const;

    QVariantList get_buff_uptime_table() const;
    virtual QVariantList get_resource_gain_table() const;
    QVariantList get_proc_table() const;
};

#endif // CLASSSTATISTICS_H
