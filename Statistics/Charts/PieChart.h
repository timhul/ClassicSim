#ifndef PIECHART_H
#define PIECHART_H

#include <QObject>
#include <QChartView>
#include <QPieSeries>

QT_CHARTS_USE_NAMESPACE

class PieChart : public QObject {
    Q_OBJECT

public:
    PieChart(QObject *parent = nullptr);

    Q_INVOKABLE QVariantList getSlices();

private:
    QPieSeries* series;
};

#endif // PIECHART_H
