#ifndef MAGESTATISTICS_H
#define MAGESTATISTICS_H

#include "ClassStatistics.h"

class MageStatistics: public ClassStatistics {
    Q_OBJECT

public:
    MageStatistics(QObject* parent = nullptr);

    void update_statistics() override;

    Q_INVOKABLE int getNumStatisticsRows() const override;
    Q_INVOKABLE QVariantList getTableInfo(const int index) const override;
    Q_INVOKABLE QVariantList getChartInfo(const int index) const override;
    Q_INVOKABLE QString getEntryIcon(const int index) const override;

private:
};

#endif // MAGESTATISTICS_H
