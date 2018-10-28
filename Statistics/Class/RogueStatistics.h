#ifndef ROGUESTATISTICS_H
#define ROGUESTATISTICS_H

#include "ClassStatistics.h"

class RogueStatistics: public ClassStatistics {
public:
    RogueStatistics(SimSettings* settings);

    Q_INVOKABLE int getNumStatisticsRows() const override;
    Q_INVOKABLE QVariantList getTableInfo(const int index) const override;
    Q_INVOKABLE QVariantList getChartInfo(const int index) const override;
    Q_INVOKABLE QString getEntryIcon(const int index) const override;

private:
};

#endif // ROGUESTATISTICS_H
