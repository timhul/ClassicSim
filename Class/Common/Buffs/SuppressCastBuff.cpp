#include "SuppressCastBuff.h"

#include "Character.h"
#include "CharacterStats.h"

SuppressCastBuff::SuppressCastBuff(Character* pchar, const QString& name, const QString& icon, const int duration, const int charges) :
    SelfBuff(pchar, name, icon, duration, charges) {}

void SuppressCastBuff::buff_effect_when_applied() {
    pchar->get_stats()->suppress_casting_time(this);
}

void SuppressCastBuff::buff_effect_when_removed() {
    pchar->get_stats()->return_casting_time(this);
}
