#ifndef PALADINSTATISTICS_H
#define PALADINSTATISTICS_H

#include "ClassStatistics.h"

class PaladinStatistics: public ClassStatistics {
public:
    PaladinStatistics(SimSettings* settings);

    Q_INVOKABLE int getNumStatisticsRows() const override;
    Q_INVOKABLE QVariantList getTableInfo(const int index) const override;
    Q_INVOKABLE QVariantList getChartInfo(const int index) const override;
    Q_INVOKABLE QString getEntryIcon(const int index) const override;

private:
};

#endif // PALADINSTATISTICS_H
