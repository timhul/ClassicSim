#ifndef STATISTICSRESOURCE_H
#define STATISTICSRESOURCE_H

#include <QString>

class StatisticsResource {
public:
    StatisticsResource(QString name);

    void reset();

    QString get_name() const;
    void add_resource_gain(const int);
    int get_resource_gain() const;

protected:
private:
    const QString name;
    int resource_gain;
};

#endif // STATISTICSRESOURCE_H
