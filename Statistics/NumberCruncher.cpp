
#include "NumberCruncher.h"
#include "ClassStatistics.h"
#include "StatisticsBuff.h"
#include "StatisticsProc.h"
#include "StatisticsResource.h"
#include "StatisticsSpell.h"
#include <cassert>
#include <QDebug>

NumberCruncher::~NumberCruncher() {
    reset();
}

void NumberCruncher::reset() {
    QMutexLocker lock(&mutex);

    QMap<SimOption, QVector<ClassStatistics*>>::const_iterator it = class_stats.constBegin();
    auto end = class_stats.constEnd();
    while(it != end) {
        for (auto & class_stats_instance : it.value())
            delete class_stats_instance;
        ++it;
    }

    class_stats.clear();
}

void NumberCruncher::add_class_statistic(SimOption key, ClassStatistics* cstat) {
    QMutexLocker lock(&mutex);
    if (!class_stats.contains(key))
        class_stats.insert(key, QVector<ClassStatistics*>({}));

    qDebug() << "Adding ClassStatistics to option" << key;

    class_stats[key].append(cstat);
}

void NumberCruncher::print() {
    QMutexLocker lock(&mutex);

    QMap<SimOption, QVector<ClassStatistics*>>::const_iterator it = class_stats.constBegin();
    auto end = class_stats.constEnd();
    while(it != end) {
        QVector<double> dps;
        for (auto & stat : it.value()) {
            dps.append(stat->get_total_dps());

            double dps_sum = 0;
            for (auto & value : dps) {
                qDebug() << "Index 1 dps " << QString::number(value, 'f', 2);
                dps_sum += value;
            }
            dps_sum /= dps.size();

            qDebug() << "For option" << it.key() << "dps was" << QString::number(dps_sum, 'f', 2);
        }
        ++it;
    }
}
