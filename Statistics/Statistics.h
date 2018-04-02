#ifndef STATISTICS_H
#define STATISTICS_H

#include <QString>
#include <QMap>
#include <math.h>

class Statistics {
public:
    int add(QString, int);
    int get_int(QString);
    int increment(QString);
    void average(QString, int);
    float get_float(QString);

    int get_total_damage();

    void dump(void);
    void clear();

protected:
private:
    void set_int(QString, int);
    void set_float(QString, float);
    QMap<QString, int> int_stats;
    QMap<QString, float> float_stats;
};

#endif // STATISTICS_H
