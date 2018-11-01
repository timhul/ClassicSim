
#include "NoEffectBuff.h"
#include <cassert>
#include <QDebug>

NoEffectBuff::NoEffectBuff(Character* pchar, const int duration, const QString &name, const QString &icon, const bool hidden):
    Buff(pchar, name, icon, duration, 0),
    linked_buff(nullptr)
{
    this->hidden = hidden;
}

void NoEffectBuff::link_buff_expiration(Buff* buff_to_cancel) {
    this->linked_buff = buff_to_cancel;
}

void NoEffectBuff::buff_effect_when_applied() {
}

void NoEffectBuff::buff_effect_when_removed() {
    if (linked_buff != nullptr)
        this->linked_buff->cancel_buff();
}
