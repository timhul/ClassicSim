#pragma once

#include "SelfBuff.h"

class HolyStrength: public SelfBuff {
public:
    HolyStrength(Character* pchar, const QString& weapon_side);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
