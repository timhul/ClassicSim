#ifndef CLASSSTATISTICS_H
#define CLASSSTATISTICS_H

#include <QObject>
#include <QVariantList>
#include <QMap>

class Statistics;
class StatisticsSpell;

class ClassStatistics : public QObject {
    Q_OBJECT

public:
    ClassStatistics(Statistics* statistics, QObject* parent = 0);

    virtual void update_statistics() = 0;
    Q_INVOKABLE virtual int getNumStatisticsRows() const = 0;
    Q_INVOKABLE virtual QVariantList getTableInfo(const int index) const = 0;
    Q_INVOKABLE virtual QVariantList getChartInfo(const int index) const = 0;
    Q_INVOKABLE virtual QString getEntryIcon(const int index) const = 0;

    void add_spell_statistics(StatisticsSpell *);

protected:
    Statistics* statistics;
    QMap<QString, StatisticsSpell*> spell_statistics;

    QVariantList get_damage_breakdown_table() const;
    QVariantList get_damage_breakdown_chart() const;

    int get_total_damage_dealt() const;
};

#endif // CLASSSTATISTICS_H
