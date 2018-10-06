#ifndef DRUIDSTATISTICS_H
#define DRUIDSTATISTICS_H

#include "ClassStatistics.h"

class DruidStatistics: public ClassStatistics {
    Q_OBJECT

public:
    DruidStatistics(QObject* parent = nullptr);

    Q_INVOKABLE int getNumStatisticsRows() const override;
    Q_INVOKABLE QVariantList getTableInfo(const int index) const override;
    Q_INVOKABLE QVariantList getChartInfo(const int index) const override;
    Q_INVOKABLE QString getEntryIcon(const int index) const override;

private:
};

#endif // DRUIDSTATISTICS_H
