#ifndef SHAMANSTATISTICS_H
#define SHAMANSTATISTICS_H

#include "ClassStatistics.h"

class ShamanStatistics: public ClassStatistics {
public:
    ShamanStatistics(SimSettings* settings);

    Q_INVOKABLE int getNumStatisticsRows() const override;
    Q_INVOKABLE QVariantList getTableInfo(const int index) const override;
    Q_INVOKABLE QVariantList getChartInfo(const int index) const override;
    Q_INVOKABLE QString getEntryIcon(const int index) const override;

private:
};

#endif // SHAMANSTATISTICS_H
