#ifndef WARRIORSTATISTICS_H
#define WARRIORSTATISTICS_H

#include "ClassStatistics.h"

class WarriorStatistics: public ClassStatistics {
    Q_OBJECT

public:
    WarriorStatistics(QObject* parent = 0);

    void update_statistics() override;

    Q_INVOKABLE int getNumStatisticsRows() const override;
    Q_INVOKABLE QVariantList getTableInfo(const int index) const override;
    Q_INVOKABLE QVariantList getChartInfo(const int index) const override;
    Q_INVOKABLE QString getEntryIcon(const int index) const override;

private:
    QVariantList get_ratio_heroic_strike_table() const;
    QVariantList get_ratio_heroic_strike_chart() const;
};

#endif // WARRIORSTATISTICS_H
