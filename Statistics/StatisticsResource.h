#pragma once

#include <QMap>
#include <QString>

#include "Resource.h"

class StatisticsResource;

bool name(StatisticsResource* lhs, StatisticsResource* rhs);
bool mana_gain(StatisticsResource* lhs, StatisticsResource* rhs);
bool rage_gain(StatisticsResource* lhs, StatisticsResource* rhs);
bool energy_gain(StatisticsResource* lhs, StatisticsResource* rhs);

class StatisticsResource {
public:
    StatisticsResource(QString name, QString icon, const int time_in_combat);

    void reset();

    QString get_name() const;
    QString get_icon() const;
    void add_resource_gain(const ResourceType, const unsigned);
    double get_mana_gain_per_5() const;
    double get_rage_gain_per_5() const;
    double get_energy_gain_per_5() const;

    void add(const StatisticsResource*);

private:
    const QString name;
    const QString icon;
    const int time_in_combat;
    QMap<ResourceType, unsigned> resource_gain;
};
