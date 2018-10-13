#ifndef PRIESTSTATISTICS_H
#define PRIESTSTATISTICS_H

#include "ClassStatistics.h"

class PriestStatistics: public ClassStatistics {
    Q_OBJECT

public:
    PriestStatistics(SimSettings* settings, QObject* parent = nullptr);

    Q_INVOKABLE int getNumStatisticsRows() const override;
    Q_INVOKABLE QVariantList getTableInfo(const int index) const override;
    Q_INVOKABLE QVariantList getChartInfo(const int index) const override;
    Q_INVOKABLE QString getEntryIcon(const int index) const override;

private:
};

#endif // PRIESTSTATISTICS_H
