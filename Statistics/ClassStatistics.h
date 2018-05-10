#ifndef CLASSSTATISTICS_H
#define CLASSSTATISTICS_H

#include <QObject>
#include <QVariantList>

class ClassStatistics : public QObject {
    Q_OBJECT

public:
    ClassStatistics(QObject* parent = 0);

    virtual void update_statistics() = 0;
    Q_INVOKABLE virtual int getNumStatisticsRows() const = 0;
    Q_INVOKABLE virtual QVariantList getTableInfo(const int index) const = 0;
    Q_INVOKABLE virtual QVariantList getChartInfo(const int index) const = 0;
    Q_INVOKABLE virtual QString getEntryIcon(const int index) const = 0;

};

#endif // CLASSSTATISTICS_H
