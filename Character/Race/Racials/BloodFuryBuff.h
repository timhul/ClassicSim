#pragma once

#include "SelfBuff.h"

class BloodFuryBuff: public SelfBuff {
public:
    BloodFuryBuff(Character* pchar);

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

private:
    unsigned applied_ap {0};
};
