
#include "NoEffectBuff.h"
#include <cassert>
#include <QDebug>

NoEffectBuff::NoEffectBuff(Character* pchar, const int duration):
    Buff(pchar, "NO_EFFECT", NO_ICON, duration, 0),
    linked_buff(nullptr)
{
    this->hidden = true;
}

void NoEffectBuff::link_buff_expiration(Buff* buff_to_cancel) {
    this->linked_buff = buff_to_cancel;
}

void NoEffectBuff::buff_effect_when_applied() {
}

void NoEffectBuff::buff_effect_when_removed() {
    this->linked_buff->cancel_buff();
}
