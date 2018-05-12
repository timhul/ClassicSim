#ifndef CLASSSTATISTICS_H
#define CLASSSTATISTICS_H

#include <QObject>
#include <QVariantList>
#include <QMap>

class StatisticsSpell;
class StatisticsBuff;
class StatisticsResource;

class ClassStatistics : public QObject {
    Q_OBJECT

public:
    ClassStatistics(QObject* parent = 0);

    virtual void update_statistics() = 0;
    Q_INVOKABLE virtual int getNumStatisticsRows() const = 0;
    Q_INVOKABLE virtual QVariantList getTableInfo(const int index) const = 0;
    Q_INVOKABLE virtual QVariantList getChartInfo(const int index) const = 0;
    Q_INVOKABLE virtual QString getEntryIcon(const int index) const = 0;

    void add_spell_statistics(StatisticsSpell *);
    void add_buff_statistics(StatisticsBuff *);
    void add_resource_statistics(StatisticsResource*);
    int get_total_damage_dealt() const;

    int get_total_damage_for_spell(const QString name);

    void reset_statistics();

protected:
    QMap<QString, StatisticsSpell*> spell_statistics;
    QMap<QString, StatisticsBuff*> buff_statistics;
    QMap<QString, StatisticsResource*> resource_statistics;

    QVariantList get_damage_breakdown_table() const;
    QVariantList get_damage_breakdown_chart() const;

    QVariantList get_buff_uptime_table() const;
    virtual QVariantList get_resource_gain_table() const;

};

#endif // CLASSSTATISTICS_H
