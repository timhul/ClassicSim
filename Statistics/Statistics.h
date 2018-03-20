#ifndef STATISTICS_H
#define STATISTICS_H

#include <QString>
#include <map>
#include <math.h>

class Statistics {
public:
    int get_int(QString);
    void set_int(QString, int);
    int add(QString, int);
    int increment(QString);
    void average(QString, int);
    float get_float(QString);
    void set_float(QString, float);

    void dump(void);

protected:
private:
    std::map<QString, int> int_stats;
    std::map<QString, float> float_stats;
};

#endif // STATISTICS_H
