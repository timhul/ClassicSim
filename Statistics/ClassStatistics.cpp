
#include "ClassStatistics.h"
#include "StatisticsSpell.h"
#include "StatisticsBuff.h"
#include "StatisticsResource.h"
#include "StatisticsProc.h"

ClassStatistics::ClassStatistics(QObject *parent) :
    QObject(parent)
{}

void ClassStatistics::add_spell_statistics(StatisticsSpell* spell) {
    // TODO: Minimize adding of spell statistics. Maybe at end of encounter/sim
    if (spell_statistics.contains(spell->get_name()))
        return;

    spell_statistics[spell->get_name()] = spell;
}

void ClassStatistics::add_buff_statistics(StatisticsBuff* buff) {
    if (buff_statistics.contains(buff->get_name()))
        return;

    buff_statistics[buff->get_name()] = buff;
}

void ClassStatistics::add_resource_statistics(StatisticsResource* resource) {
    if (resource_statistics.contains(resource->get_name()))
        return;

    resource_statistics[resource->get_name()] = resource;
}

void ClassStatistics::add_proc_statistics(StatisticsProc* proc) {
    if (proc_statistics.contains(proc->get_name()))
        return;

    proc_statistics[proc->get_name()] = proc;
}

void ClassStatistics::remove_spell_statistics(const QString& key) {
    if (!spell_statistics.contains(key))
        return;

    spell_statistics.remove(key);
}

void ClassStatistics::remove_buff_statistics(const QString& key) {
    if (!buff_statistics.contains(key))
        return;

    buff_statistics.remove(key);
}

void ClassStatistics::remove_resource_statistics(const QString& key) {
    if (!resource_statistics.contains(key))
        return;

    resource_statistics.remove(key);
}

void ClassStatistics::remove_proc_statistics(const QString& key) {
    if (!proc_statistics.contains(key))
        return;

    proc_statistics.remove(key);
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
        double uptime = it.value()->get_uptime();
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
        int gain = it.value()->get_resource_gain();
        if (gain == 0) {
            ++it;
            continue;
        }

        QString name = it.value()->get_name();
        // TODO: Remove hardcoded knowledge of num fights / fight length
        double gain_per_5 = double(gain) / ((double(300) / 5) * 1000);
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
        double proc_rate = it.value()->get_proc_rate();
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

void ClassStatistics::reset_statistics() {
    QMap<QString, StatisticsSpell*>::const_iterator it_spell = spell_statistics.constBegin();
    auto end_spell = spell_statistics.constEnd();
    while(it_spell != end_spell) {
        it_spell.value()->reset();
        ++it_spell;
    }

    QMap<QString, StatisticsBuff*>::const_iterator it_buff = buff_statistics.constBegin();
    auto end_buff = buff_statistics.constEnd();
    while(it_buff != end_buff) {
        it_buff.value()->reset();
        ++it_buff;
    }

    QMap<QString, StatisticsResource*>::const_iterator it_resource = resource_statistics.constBegin();
    auto end_resource = resource_statistics.constEnd();
    while(it_resource != end_resource) {
        it_resource.value()->reset();
        ++it_resource;
    }

    QMap<QString, StatisticsProc*>::const_iterator it_proc = proc_statistics.constBegin();
    auto end_proc = proc_statistics.constEnd();
    while(it_proc != end_proc) {
        it_proc.value()->reset();
        ++it_proc;
    }
}
