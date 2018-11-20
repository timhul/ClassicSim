#ifndef STATISTICSRESOURCE_H
#define STATISTICSRESOURCE_H

#include "Resource.h"

#include <QString>
#include <QMap>

class StatisticsResource;

bool name(StatisticsResource* lhs, StatisticsResource* rhs);
bool mana_gain(StatisticsResource* lhs, StatisticsResource* rhs);
bool rage_gain(StatisticsResource* lhs, StatisticsResource* rhs);
bool energy_gain(StatisticsResource* lhs, StatisticsResource* rhs);

class StatisticsResource {
public:
    StatisticsResource(const QString& name, const QString& icon);

    void reset();

    QString get_name() const;
    QString get_icon() const;
    void add_resource_gain(const ResourceType, const unsigned);
    unsigned get_mana_gain() const;
    unsigned get_rage_gain() const;
    unsigned get_energy_gain() const;

    void add(const StatisticsResource*);

protected:
private:
    const QString name;
    const QString icon;
    QMap<ResourceType, unsigned> resource_gain;
};

#endif // STATISTICSRESOURCE_H
