#pragma once

#include <QString>
#include <QMap>

#include "ItemStatsEnum.h"
#include "PhaseRequirer.h"

class Stats;

class RandomAffix : public PhaseRequirer
{
public:
    RandomAffix(unsigned id, Content::Phase required_phase, const QString& name, Stats* stats, const QStringList &stats_list, const QMap<ItemStats, unsigned> &affix_stat_values);
    ~RandomAffix();
    QString to_string() const;
    Stats* get_stats() const;
    QStringList get_stats_list() const;
    QMap<ItemStats, unsigned> get_affix_stat_values() const;

    const unsigned id;
    const QString name;

private:
    Stats* stats;
    QStringList stats_list;
    QMap<ItemStats, unsigned> affix_stat_values;
};

