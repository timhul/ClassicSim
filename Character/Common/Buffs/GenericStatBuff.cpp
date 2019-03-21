#include "GenericStatBuff.h"

#include "Character.h"
#include "CharacterStats.h"

GenericStatBuff::GenericStatBuff(Character* pchar,
                                 const QString& name,
                                 const QString& icon,
                                 const int duration,
                                 const ItemStats stat_type,
                                 const unsigned value):
    Buff(pchar, name, icon, duration, 0),
    stat_type(stat_type),
    stat_value(value)
{}

void GenericStatBuff::buff_effect_when_applied() {
    pchar->get_stats()->increase_stat(stat_type, stat_value);
}

void GenericStatBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_stat(stat_type, stat_value);
}
