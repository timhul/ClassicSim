
#include "ClassStatistics.h"
#include "StatisticsSpell.h"
#include "StatisticsBuff.h"
#include "StatisticsResource.h"
#include "StatisticsProc.h"
#include <QDebug>

ClassStatistics::ClassStatistics(SimSettings* sim_settings) :
    sim_settings(sim_settings),
    option(SimOption::NoScale),
    combat_iterations(0),
    combat_length(0)
{}

ClassStatistics::~ClassStatistics() {
    delete_maps();
}

void ClassStatistics::set_sim_option(const SimOption option) {
    assert(this->option == SimOption::NoScale);
    this->option = option;
}

SimOption ClassStatistics::get_sim_option() const {
    return this->option;
}

StatisticsSpell* ClassStatistics::get_spell_statistics(const QString &name, const QString& icon) {
    assert(!spell_statistics.contains(name));

    spell_statistics[name] = new StatisticsSpell(name, icon);
    return spell_statistics[name];
}

StatisticsBuff* ClassStatistics::get_buff_statistics(const QString& name, const QString& icon, const bool debuff) {
    assert(!buff_statistics.contains(name));

    buff_statistics[name] = new StatisticsBuff(name, icon, debuff);
    return buff_statistics[name];
}

StatisticsResource *ClassStatistics::get_resource_statistics(const QString& name, const QString& icon) {
    assert(!resource_statistics.contains(name));

    resource_statistics[name] = new StatisticsResource(name, icon);
    return resource_statistics[name];
}

StatisticsProc *ClassStatistics::get_proc_statistics(const QString& name, const QString& icon) {
    assert(!proc_statistics.contains(name));

    proc_statistics[name] = new StatisticsProc(name, icon);
    return proc_statistics[name];
}

bool variant_list_greater_than(const QVariantList &list1, const QVariantList &list2) {
    if (list1.size() < 2)
        return false;
    if (list2.size() < 2)
        return true;

    return list1[1] > list2[1];
}

QVariantList ClassStatistics::get_damage_breakdown_table() const {
    int total_damage_dealt = get_total_damage_dealt();

    QVector<QVariantList> dmg_entries;

    QMap<QString, StatisticsSpell*>::const_iterator it = spell_statistics.constBegin();
    auto end = spell_statistics.constEnd();
    while(it != end) {
        int dmg = it.value()->get_total_dmg_dealt();
        if (dmg == 0) {
            ++it;
            continue;
        }

        QString name = it.value()->get_name();
        double percentage = double(dmg) / double(total_damage_dealt);
        dmg_entries.append(QVariantList({name, dmg, QString::number(percentage * 100, 'f', 2) + "%"}));
        ++it;
    }

    QVariantList info;
    if (dmg_entries.empty())
        return info;

    QVariantList columns  = {"Ability", "Total Damage", "Percentage"};
    info.append(columns.size());
    info.append(columns);

    std::sort(dmg_entries.begin(), dmg_entries.end(), variant_list_greater_than);

    for (const auto & dmg_entry : dmg_entries) {
        info.append(dmg_entry);
    }

    return info;
}

QVariantList ClassStatistics::get_damage_breakdown_chart() const {
    QVariantList info;

    info.append("Total Damage Breakdown");
    info.append("PIE");

    QMap<QString, StatisticsSpell*>::const_iterator it = spell_statistics.constBegin();
    auto end = spell_statistics.constEnd();
    while(it != end) {
        int dmg = it.value()->get_total_dmg_dealt();
        if (dmg == 0) {
            ++it;
            continue;
        }

        QString name = it.value()->get_name();
        info.append(QVariantList({name, dmg, "#edbd00"}));
        ++it;
    }

    return info;
}

QVariantList ClassStatistics::get_buff_uptime_table() const {
    QVector<QVariantList> uptime_entries;

    QMap<QString, StatisticsBuff*>::const_iterator it = buff_statistics.constBegin();
    auto end = buff_statistics.constEnd();
    while(it != end) {
        double uptime = it.value()->get_avg_uptime();
        if (uptime < double(0.00001)) {
            ++it;
            continue;
        }

        QString name = it.value()->get_name();
        uptime_entries.append(QVariantList({name, uptime, QString::number(uptime * 100, 'f', 2) + "%"}));
        ++it;
    }

    QVariantList info;
    if (uptime_entries.empty())
        return info;

    QVariantList columns  = {"Buff", "Uptime"};
    info.append(columns.size());
    info.append(columns);

    std::sort(uptime_entries.begin(), uptime_entries.end(), variant_list_greater_than);

    for (auto & uptime_entry : uptime_entries) {
        QVariantList pruned = {uptime_entry[0], uptime_entry[2]};
        info.append(pruned);
    }

    return info;
}

QVariantList ClassStatistics::get_resource_gain_table() const {
    QVector<QVariantList> entries;

    QMap<QString, StatisticsResource*>::const_iterator it = resource_statistics.constBegin();
    auto end = resource_statistics.constEnd();
    while(it != end) {
        int gain = it.value()->get_rage_gain();
        if (gain == 0) {
            ++it;
            continue;
        }

        QString name = it.value()->get_name();

        double gain_per_5 = double(gain) / ((double(combat_length) / 5) * combat_iterations);
        entries.append(QVariantList({name, gain, QString::number(gain_per_5, 'f', 2)}));
        ++it;
    }

    QVariantList info;
    if (entries.empty())
        return info;

    QVariantList columns  = {"Source", "Resource Gain per 5s"};
    info.append(columns.size());
    info.append(columns);
    std::sort(entries.begin(), entries.end(), variant_list_greater_than);

    for (auto & entry : entries) {
        QVariantList pruned = {entry[0], entry[2]};
        info.append(pruned);
    }

    return info;
}

QVariantList ClassStatistics::get_proc_table() const {
    QVector<QVariantList> entries;

    QMap<QString, StatisticsProc*>::const_iterator it = proc_statistics.constBegin();
    auto end = proc_statistics.constEnd();
    while(it != end) {
        int procs = it.value()->get_procs();
        if (procs == 0) {
            ++it;
            continue;
        }

        QString name = it.value()->get_name();
        double proc_rate = it.value()->get_avg_proc_rate();
        entries.append(QVariantList({name, proc_rate, QString::number(proc_rate * 100, 'f', 2), procs}));
        ++it;
    }

    QVariantList info;
    if (entries.empty())
        return info;

    QVariantList columns  = {"Source", "Procs", "Proc %"};
    info.append(columns.size());
    info.append(columns);
    std::sort(entries.begin(), entries.end(), variant_list_greater_than);

    for (auto & entry : entries) {
        QVariantList pruned = {entry[0], entry[3], entry[2]};
        info.append(pruned);
    }

    return info;
}

int ClassStatistics::get_total_damage_dealt() const {
    int sum = 0;

    QMap<QString, StatisticsSpell*>::const_iterator it = spell_statistics.constBegin();
    auto end = spell_statistics.constEnd();
    while(it != end) {
        sum += it.value()->get_total_dmg_dealt();
        ++it;
    }

    return sum;
}

double ClassStatistics::get_total_dps() const {
    int damage_dealt = get_total_damage_dealt();

    return static_cast<double>(damage_dealt) / (combat_iterations * combat_length);
}

int ClassStatistics::get_total_damage_for_spell(const QString& name) const {
    if (!spell_statistics.contains(name))
        return 0;

    return spell_statistics[name]->get_total_dmg_dealt();
}

int ClassStatistics::get_total_attempts_for_spell(const QString& name) const {
    if (!spell_statistics.contains(name))
        return 0;

    return spell_statistics[name]->get_total_attempts_made();
}

void ClassStatistics::prepare_statistics() {
    delete_maps();

    combat_iterations = sim_settings->get_combat_iterations_full_sim();
    combat_length = sim_settings->get_combat_length();
}

void ClassStatistics::delete_maps() {
    QMap<QString, StatisticsSpell*>::const_iterator it_spell = spell_statistics.constBegin();
    auto end_spell = spell_statistics.constEnd();
    while(it_spell != end_spell) {
        delete it_spell.value();
        ++it_spell;
    }

    QMap<QString, StatisticsBuff*>::const_iterator it_buff = buff_statistics.constBegin();
    auto end_buff = buff_statistics.constEnd();
    while(it_buff != end_buff) {
        delete it_buff.value();
        ++it_buff;
    }

    QMap<QString, StatisticsResource*>::const_iterator it_resource = resource_statistics.constBegin();
    auto end_resource = resource_statistics.constEnd();
    while(it_resource != end_resource) {
        delete it_resource.value();
        ++it_resource;
    }

    QMap<QString, StatisticsProc*>::const_iterator it_proc = proc_statistics.constBegin();
    auto end_proc = proc_statistics.constEnd();
    while(it_proc != end_proc) {
        delete it_proc.value();
        ++it_proc;
    }

    spell_statistics.clear();
    buff_statistics.clear();
    resource_statistics.clear();
    proc_statistics.clear();
}
