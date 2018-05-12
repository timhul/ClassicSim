#ifndef CLASSSTATISTICS_H
#define CLASSSTATISTICS_H

#include <QObject>
#include <QVariantList>
#include <QMap>

class StatisticsSpell;

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
    int get_total_damage_dealt() const;

    int get_total_damage_for_spell(const QString name);

    void reset_statistics();

protected:
    QMap<QString, StatisticsSpell*> spell_statistics;

    QVariantList get_damage_breakdown_table() const;
    QVariantList get_damage_breakdown_chart() const;

};

#endif // CLASSSTATISTICS_H
