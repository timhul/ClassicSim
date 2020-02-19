#pragma once

#include "SelfBuff.h"

class SuppressCastBuff : public SelfBuff {
public:
    SuppressCastBuff(Character* pchar, const QString& name, const QString& icon, const int duration, const int charges);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
