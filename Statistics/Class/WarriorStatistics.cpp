
#include "WarriorStatistics.h"

WarriorStatistics::WarriorStatistics(SimSettings *settings, QObject *parent) :
    ClassStatistics(settings, parent)
{

}

int WarriorStatistics::getNumStatisticsRows() const {
    // TODO: Check how many of the possible statistic entries actually have statistics.
    // That is, to show e.g. Bloodthirst damage, there must be some Bloodthirst statistics.
    int data = spell_statistics.empty() ? 0 : 1;
    data += buff_statistics.empty() ? 0 : 1;
    data += resource_statistics.empty() ? 0 : 1;
    data += proc_statistics.empty() ? 0 : 1;
    return data;
}

QVariantList WarriorStatistics::getTableInfo(const int index) const {
    QVariantList table_info;

    switch (index) {
    case 0:
        table_info.append(get_damage_breakdown_table());
        break;
    case 1:
        table_info.append(get_buff_uptime_table());
        break;
    case 2:
        table_info.append(get_resource_gain_table());
        break;
    case 3:
        table_info.append(get_proc_table());
        break;
    }

    return table_info;
}

QVariantList WarriorStatistics::getChartInfo(const int index) const {
    QVariantList chart_info;


    switch (index) {
    case 0:
        chart_info.append(get_damage_breakdown_chart());
        break;
    }

    return chart_info;
}

QString WarriorStatistics::getEntryIcon(const int) const {
    // TODO: Refactor the knowledge of exact icon path (also listed in Improved Heroic Strike)
    // return "Assets/warrior/arms/tier1/Ability_rogue_ambush.png";
    return "";
}

QVariantList WarriorStatistics::get_ratio_heroic_strike_table() const {
    QVariantList info;

    info.append(QVariant(3));
    info.append(QVariantList({"Ability", "Total Amount", "Percentage"}));
    info.append(QVariantList({"Heroic Strike", "105", "52.5%"}));
    info.append(QVariantList({"Mainhand Attack", "95", "47.5%"}));

    return info;
}

QVariantList WarriorStatistics::get_ratio_heroic_strike_chart() const {
    QVariantList info;

    info.append("Ratio Heroic Strike to Mainhand Swing");
    info.append("PIE");

    info.append("52.5% HS");
    info.append(52.5);
    info.append("#edbd00");

    info.append("47.5% MH Auto");
    info.append(100-52.5);
    info.append("#e5e4e0");

    return info;
}
