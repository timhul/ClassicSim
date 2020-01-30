#include "RandomAffix.h"

#include "Stats.h"

RandomAffix::RandomAffix(unsigned id, Content::Phase required_phase, const QString& name, Stats* stats, const QStringList &stats_list, const QMap<ItemStats, unsigned> &affix_stat_values) :
    PhaseRequirer(required_phase),
    id(id),
    name(name),
    stats(std::move(stats)),
    stats_list(stats_list),
    affix_stat_values(affix_stat_values)
{}

unsigned RandomAffix::get_id() const
{
    return id;
}

QString RandomAffix::get_name() const
{
    return name;
}

QString RandomAffix::to_string() const
{
    return QStringLiteral("%1 (%2)").arg(name).arg(stats_list.join(","));
}

Stats *RandomAffix::get_stats() const
{
    return this->stats;
}

QStringList RandomAffix::get_stats_list() const
{
    return this->stats_list;
}

QMap<ItemStats, unsigned> RandomAffix::get_affix_stat_values() const
{
    return this->affix_stat_values;
}
