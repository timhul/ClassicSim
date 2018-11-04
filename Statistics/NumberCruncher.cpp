
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

    QMap<SimOption::Name, QVector<ClassStatistics*>>::const_iterator it = class_stats.constBegin();
    auto end = class_stats.constEnd();
    while(it != end) {
        for (auto & class_stats_instance : it.value())
            delete class_stats_instance;
        ++it;
    }

    class_stats.clear();
}

void NumberCruncher::add_class_statistic(SimOption::Name key, ClassStatistics* cstat) {
    QMutexLocker lock(&mutex);
    if (!class_stats.contains(key))
        class_stats.insert(key, QVector<ClassStatistics*>({}));

    class_stats[key].append(cstat);
}

void NumberCruncher::merge_spell_stats(QList<StatisticsSpell *> &vec) {
    QMutexLocker lock(&mutex);

    assert(class_stats.contains(SimOption::Name::NoScale));

    long long int total_damage_dealt = 0;
    for (auto & cstats : class_stats[SimOption::Name::NoScale]) {
        total_damage_dealt += cstats->get_total_damage_dealt();
    }

    QSet<QString> handled_entries;
    for (auto & cstats : class_stats[SimOption::Name::NoScale]) {
        QMap<QString, StatisticsSpell*>::const_iterator it = cstats->spell_statistics.constBegin();
        auto end = cstats->spell_statistics.constEnd();
        while (it != end) {
            if (handled_entries.contains(it.key())) {
                ++it;
                continue;
            }
            handled_entries.insert(it.key());
            merge_spell_entry(it.key(), it.value()->get_icon(), total_damage_dealt, vec);
            ++it;
        }
    }
}

void NumberCruncher::merge_spell_entry(const QString& name, const QString& icon, long long total_damage_dealt, QList<StatisticsSpell *> &vec) {
    StatisticsSpell* result = new StatisticsSpell(name, icon);
    for (auto & cstats : class_stats[SimOption::Name::NoScale]) {
        if (!cstats->spell_statistics.contains(name))
            continue;

        result->add(cstats->spell_statistics[name]);
    }

    result->set_percentage_of_damage_dealt(total_damage_dealt);
    vec.append(result);
}

void NumberCruncher::merge_buff_stats(QList<StatisticsBuff*>& vec, const bool include_debuffs) {
    QMutexLocker lock(&mutex);

    assert(class_stats.contains(SimOption::Name::NoScale));

    QSet<QString> handled_entries;
    for (auto & cstats : class_stats[SimOption::Name::NoScale]) {
        QMap<QString, StatisticsBuff*>::const_iterator it = cstats->buff_statistics.constBegin();
        auto end = cstats->buff_statistics.constEnd();
        while (it != end) {
            if (handled_entries.contains(it.key()) || (it.value()->is_debuff() != include_debuffs)) {
                ++it;
                continue;
            }
            handled_entries.insert(it.key());
            merge_buff_entry(it.key(), it.value()->get_icon(), vec);
            ++it;
        }
    }
}

void NumberCruncher::merge_buff_entry(const QString& name, const QString &icon, QList<StatisticsBuff*>& vec) {
    auto* result = new StatisticsBuff(name, icon, false);
    for (auto & cstats : class_stats[SimOption::Name::NoScale]) {
        if (!cstats->buff_statistics.contains(name))
            continue;

        result->add(cstats->buff_statistics[name]);
    }

    if (result->get_avg_uptime() < 0.0000001)
        return;

    vec.append(result);
}

void NumberCruncher::merge_proc_stats(QList<StatisticsProc*>& vec) {
    QMutexLocker lock(&mutex);

    assert(class_stats.contains(SimOption::Name::NoScale));

    QSet<QString> handled_entries;
    for (auto & cstats : class_stats[SimOption::Name::NoScale]) {
        QMap<QString, StatisticsProc*>::const_iterator it = cstats->proc_statistics.constBegin();
        auto end = cstats->proc_statistics.constEnd();
        while (it != end) {
            if (handled_entries.contains(it.key())) {
                ++it;
                continue;
            }
            handled_entries.insert(it.key());
            merge_proc_entry(it.key(), it.value()->get_icon(), vec);
            ++it;
        }
    }
}

void NumberCruncher::merge_proc_entry(const QString& name, const QString &icon, QList<StatisticsProc*>& vec) {
    auto* result = new StatisticsProc(name, icon);
    for (auto & cstats : class_stats[SimOption::Name::NoScale]) {
        if (!cstats->proc_statistics.contains(name))
            continue;

        result->add(cstats->proc_statistics[name]);
    }

    vec.append(result);
}

void NumberCruncher::merge_resource_stats(QList<StatisticsResource*>& vec) {
    QMutexLocker lock(&mutex);

    assert(class_stats.contains(SimOption::Name::NoScale));

    QSet<QString> handled_entries;
    for (auto & cstats : class_stats[SimOption::Name::NoScale]) {
        QMap<QString, StatisticsResource*>::const_iterator it = cstats->resource_statistics.constBegin();
        auto end = cstats->resource_statistics.constEnd();
        while (it != end) {
            if (handled_entries.contains(it.key())) {
                ++it;
                continue;
            }
            handled_entries.insert(it.key());
            merge_resource_entry(it.key(), it.value()->get_icon(), vec);
            ++it;
        }
    }
}

void NumberCruncher::merge_resource_entry(const QString& name, const QString &icon, QList<StatisticsResource*>& vec) {
    auto* result = new StatisticsResource(name, icon);
    for (auto & cstats : class_stats[SimOption::Name::NoScale]) {
        if (!cstats->resource_statistics.contains(name))
            continue;

        result->add(cstats->resource_statistics[name]);
    }

    vec.append(result);
}

void NumberCruncher::calculate_stat_weights(QList<ScaleResult*>& list) {
    QMutexLocker lock(&mutex);

    QMap<SimOption::Name, double> dps_per_option;

    QMap<SimOption::Name, QVector<ClassStatistics*>>::const_iterator it = class_stats.constBegin();
    auto end = class_stats.constEnd();
    while(it != end) {
        dps_per_option.insert(it.key(), get_dps_for_option(it.key()));
        ++it;
    }

    assert(dps_per_option.contains(SimOption::Name::NoScale));

    double base_value = dps_per_option.take(SimOption::Name::NoScale);

    QMap<SimOption::Name, double>::const_iterator dps_it = dps_per_option.constBegin();
    while(dps_it != dps_per_option.constEnd()) {
        double absolute_diff = dps_it.value() - base_value;
        double relative_diff = absolute_diff / base_value;

        list.append(new ScaleResult(dps_it.key(), absolute_diff, relative_diff));
        ++dps_it;
    }
}

double NumberCruncher::get_total_dps(SimOption::Name option) const {
    return get_dps_for_option(option);
}

double NumberCruncher::get_dps_for_option(SimOption::Name option) const {
    assert(class_stats.contains(option));

    QVector<double> dps;
    for (auto & class_stat : class_stats[option]) {
        dps.append(class_stat->get_total_dps());
    }

    double dps_sum = 0;
    for (auto & value : dps)
        dps_sum += value;

    dps_sum /= dps.size();

    return dps_sum;
}

double NumberCruncher::delta(double lhs, double rhs) {
    return (lhs - rhs) < 0 ?  (lhs - rhs) * - 1 : (lhs - rhs);
}

QString get_name_for_option(const SimOption::Name option) {
    if (option == SimOption::Name::ScaleAgility)
        return "+10 Agility";
    if (option == SimOption::Name::ScaleStrength)
        return "+10 Strength";
    if (option == SimOption::Name::ScaleHitChance)
        return "+1% Hit Chance";
    if (option == SimOption::Name::ScaleCritChance)
        return "+1% Crit Chance";
    if (option == SimOption::Name::ScaleMeleeAP)
        return "+10 Melee AP";
    if (option == SimOption::Name::ScaleAxeSkill)
        return "+1 Axe Skill";
    if (option == SimOption::Name::ScaleDaggerSkill)
        return "+1 Dagger Skill";
    if (option == SimOption::Name::ScaleMaceSkill)
        return "+1 Mace Skill";
    if (option == SimOption::Name::ScaleSwordSkill)
        return "+1 Sword Skill";

    return "<unset scale name>";
}
