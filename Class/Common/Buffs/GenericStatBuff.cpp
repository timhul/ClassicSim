#include "GenericStatBuff.h"

#include "Character.h"
#include "CharacterStats.h"

GenericStatBuff::GenericStatBuff(Character* pchar,
                                 const QString& name,
                                 const QString& icon,
                                 const int duration,
                                 const QVector<QPair<ItemStats, unsigned>>& stat_type_values_):
    SelfBuff(pchar, name, icon, duration, 0),
    stat_type_values(stat_type_values_)
{}

void GenericStatBuff::buff_effect_when_applied() {
    for (const auto & stat_type : stat_type_values)
        pchar->get_stats()->increase_stat(stat_type.first, stat_type.second);
}

void GenericStatBuff::buff_effect_when_removed() {
    for (const auto & stat_type : stat_type_values)
        pchar->get_stats()->decrease_stat(stat_type.first, stat_type.second);
}
