#ifndef STATISTICS_H
#define STATISTICS_H

#include <map>
#include <iostream>
#include <iomanip>
#include <math.h>

class Statistics {
public:
    int get_int(std::string);
    void set_int(std::string, int);
    int add(std::string, int);
    int increment(std::string);
    void average(std::string, int);
    float get_float(std::string);
    void set_float(std::string, float);

    void dump(void);

protected:
private:
    std::map<std::string, int> int_stats;
    std::map<std::string, float> float_stats;
};

#endif // STATISTICS_H
