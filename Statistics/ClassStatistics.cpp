
#include "ClassStatistics.h"
#include "StatisticsSpell.h"

ClassStatistics::ClassStatistics(Statistics *statistics, QObject *parent) :
    QObject(parent),
    statistics(statistics)
{}

void ClassStatistics::add_spell_statistics(StatisticsSpell* spell) {
    // TODO: Minimize adding of spell statistics. Maybe at end of encounter/sim
    if (spell_statistics.contains(spell->get_name()))
        return;

    spell_statistics[spell->get_name()] = spell;
}

QVariantList ClassStatistics::get_damage_breakdown_table() const {
    QVariantList info;

    int total_damage_dealt = get_total_damage_dealt();

    info.append(spell_statistics.size());
    info.append(QVariantList({"Ability", "Total Damage", "Percentage"}));

    for (auto it : spell_statistics.keys()) {
        QString name = spell_statistics.value(it)->get_name();
        int dmg = spell_statistics.value(it)->get_total_dmg_dealt();
        float percentage = float(dmg) / float(total_damage_dealt);
        info.append(QVariantList({name, dmg, QString::number(percentage, 'f', 2)}));
    }

    return info;
}

QVariantList ClassStatistics::get_damage_breakdown_chart() const {
    QVariantList info;

    info.append("Total Damage Breakdown");
    info.append("PIE");

    info.append("52.5% HS");
    info.append(52.5);
    info.append("#edbd00");

    info.append("47.5% MH Auto");
    info.append(100-52.5);
    info.append("#e5e4e0");

    for (auto it : spell_statistics.keys()) {
        QString name = spell_statistics.value(it)->get_name();
        int dmg = spell_statistics.value(it)->get_total_dmg_dealt();
        info.append(QVariantList({name, dmg, "#edbd00"}));
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
