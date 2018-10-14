#ifndef NUMBERCRUNCHER_H
#define NUMBERCRUNCHER_H

#include <QMap>
#include <QMutexLocker>
#include <QVector>
#include "SimSettings.h"

class ClassStatistics;

class NumberCruncher {
public:
    ~NumberCruncher();

    void add_class_statistic(SimOption, ClassStatistics*);
    void reset();

    void print();

private:
    QMutex mutex;
    QMap<SimOption, QVector<ClassStatistics*>> class_stats;
};

#endif // NUMBERCRUNCHER_H