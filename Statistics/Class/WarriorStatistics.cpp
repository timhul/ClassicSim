
#include "WarriorStatistics.h"

WarriorStatistics::WarriorStatistics(QObject *parent) :
    ClassStatistics(parent)
{

}

void WarriorStatistics::update_statistics() {
    // TODO: Find all valid entries
}

int WarriorStatistics::getNumStatisticsRows() const {
    // TODO: Check how many of the possible statistic entries actually have statistics.
    // That is, to show e.g. Bloodthirst damage, there must be some Bloodthirst statistics.
    return 1;
}

QVariantList WarriorStatistics::getTableInfo(const int) const {
    QVariantList table_info;

    table_info.append(get_ratio_heroic_strike_table());

    return table_info;
}

QVariantList WarriorStatistics::getChartInfo(const int) const {
    QVariantList chart_info;

    chart_info.append(get_ratio_heroic_strike_chart());

    return chart_info;
}

QString WarriorStatistics::getEntryIcon(const int) const {
    // TODO: Refactor the knowledge of exact icon path (also listed in Improved Heroic Strike)
    return "Assets/warrior/arms/tier1/Ability_rogue_ambush.png";
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
