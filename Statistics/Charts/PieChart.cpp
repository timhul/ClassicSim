
#include "PieChart.h"

QT_CHARTS_USE_NAMESPACE

PieChart::PieChart(QObject *parent) :
    QObject(parent),
    series(new QPieSeries())
{
    series->append("Jane", 1);
    series->append("Joe", 2);
}

QVariantList PieChart::getSlices() {
    return QVariantList({"Jane", 1, "Joe", 2});
}
