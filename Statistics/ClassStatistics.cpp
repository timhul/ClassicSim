
#include "ClassStatistics.h"
#include "StatisticsSpell.h"
#include "StatisticsBuff.h"

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

bool variant_list_greater_than(const QVariantList &list1, const QVariantList &list2) {
    if (list1.size() < 2)
        return false;
    if (list2.size() < 2)
        return true;

    return list1[1] > list2[1];
}

QVariantList ClassStatistics::get_damage_breakdown_table() const {
    QVariantList info;

    int total_damage_dealt = get_total_damage_dealt();

    QVariantList columns  = {"Ability", "Total Damage", "Percentage"};
    info.append(columns.size());
    info.append(columns);

    QVector<QVariantList> dmg_entries;

    for (auto it : spell_statistics.keys()) {
        int dmg = spell_statistics.value(it)->get_total_dmg_dealt();
        if (dmg == 0)
            continue;

        QString name = spell_statistics.value(it)->get_name();
        float percentage = float(dmg) / float(total_damage_dealt);
        dmg_entries.append(QVariantList({name, dmg, QString::number(percentage * 100, 'f', 2) + "%"}));
    }

    std::sort(dmg_entries.begin(), dmg_entries.end(), variant_list_greater_than);

    for (int i = 0; i < dmg_entries.size(); ++i) {
        info.append(dmg_entries[i]);
    }

    return info;
}

QVariantList ClassStatistics::get_damage_breakdown_chart() const {
    QVariantList info;

    info.append("Total Damage Breakdown");
    info.append("PIE");

    for (auto it : spell_statistics.keys()) {
        int dmg = spell_statistics.value(it)->get_total_dmg_dealt();
        if (dmg == 0)
            continue;

        QString name = spell_statistics.value(it)->get_name();
        info.append(QVariantList({name, dmg, "#edbd00"}));
    }

    return info;
}

QVariantList ClassStatistics::get_buff_uptime_table() const {
    QVariantList info;

    QVariantList columns  = {"Buff", "Uptime"};
    info.append(columns.size());
    info.append(columns);

    QVector<QVariantList> uptime_entries;

    for (auto it : buff_statistics.keys()) {
        float uptime = buff_statistics.value(it)->get_uptime();
        if (uptime < 0.00001)
            continue;

        QString name = buff_statistics.value(it)->get_name();
        uptime_entries.append(QVariantList({name, uptime, QString::number(uptime * 100, 'f', 2) + "%"}));
    }

    std::sort(uptime_entries.begin(), uptime_entries.end(), variant_list_greater_than);

    for (int i = 0; i < uptime_entries.size(); ++i) {
        QVariantList pruned = {uptime_entries[i][0], uptime_entries[i][2]};
        info.append(pruned);
    }

    return info;
}

int ClassStatistics::get_total_damage_dealt() const {
    int sum = 0;
    for (auto it : spell_statistics.keys()) {
        sum += spell_statistics.value(it)->get_total_dmg_dealt();
    }

    return sum;
}
int ClassStatistics::get_total_damage_for_spell(const QString name) {
    if (!spell_statistics.contains(name))
        return 0;

    return spell_statistics[name]->get_total_dmg_dealt();
}

void ClassStatistics::reset_statistics() {
    for (auto it : spell_statistics.keys()) {
        spell_statistics.value(it)->reset();
    }

    for (auto it : buff_statistics.keys()) {
        buff_statistics.value(it)->reset();
    }
}
