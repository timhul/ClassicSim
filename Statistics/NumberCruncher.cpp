
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

    QMap<SimOption, QVector<ClassStatistics*>>::const_iterator it = class_stats.constBegin();
    auto end = class_stats.constEnd();
    while(it != end) {
        for (auto & class_stats_instance : it.value())
            delete class_stats_instance;
        ++it;
    }

    class_stats.clear();
}

void NumberCruncher::add_class_statistic(SimOption key, ClassStatistics* cstat) {
    QMutexLocker lock(&mutex);
    if (!class_stats.contains(key))
        class_stats.insert(key, QVector<ClassStatistics*>({}));

    class_stats[key].append(cstat);
}

void NumberCruncher::merge_spell_stats(QList<StatisticsSpell *> &vec) {
    QMutexLocker lock(&mutex);

    assert(class_stats.contains(SimOption::NoScale));

    long long int total_damage_dealt = 0;
    for (auto & cstats : class_stats[SimOption::NoScale]) {
        total_damage_dealt += cstats->get_total_damage_dealt();
    }

    QSet<QString> handled_entries;
    for (auto & cstats : class_stats[SimOption::NoScale]) {
        QMap<QString, StatisticsSpell*>::const_iterator it = cstats->spell_statistics.constBegin();
        auto end = cstats->spell_statistics.constEnd();
        while (it != end) {
            if (handled_entries.contains(it.key())) {
                ++it;
                continue;
            }
            handled_entries.insert(it.key());
            merge_spell_entry(it.key(), total_damage_dealt, vec);
            ++it;
        }
    }
}

void NumberCruncher::merge_spell_entry(const QString& name, long long total_damage_dealt, QList<StatisticsSpell *> &vec) {
    StatisticsSpell* result = new StatisticsSpell(name);
    for (auto & cstats : class_stats[SimOption::NoScale]) {
        if (!cstats->spell_statistics.contains(name))
            continue;

        result->add(cstats->spell_statistics[name]);
    }

    result->set_percentage_of_damage_dealt(total_damage_dealt);
    vec.append(result);
}

void NumberCruncher::print() {
    QMutexLocker lock(&mutex);

    calculate_stat_weights();
}

void NumberCruncher::calculate_stat_weights() const {
    QMap<SimOption, double> dps_per_option;

    QMap<SimOption, QVector<ClassStatistics*>>::const_iterator it = class_stats.constBegin();
    auto end = class_stats.constEnd();
    while(it != end) {
        dps_per_option.insert(it.key(), get_dps_for_option(it.key()));
        ++it;
    }

    assert(dps_per_option.contains(SimOption::NoScale));

    double base_value = dps_per_option.take(SimOption::NoScale);

    QMap<SimOption, QString> percentage_increases;

    QMap<SimOption, double>::const_iterator dps_it = dps_per_option.constBegin();
    auto dps_end = dps_per_option.constEnd();
    while(dps_it != dps_end) {
        double percentage_diff = (dps_it.value() - base_value) / base_value;

        percentage_increases.insert(dps_it.key(), QString::number(percentage_diff * 100, 'f', 2));
        ++dps_it;
    }

    qDebug() << "percentage increases per stat" << percentage_increases;
}

double NumberCruncher::get_dps_for_option(SimOption option) const {
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
