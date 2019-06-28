#pragma once

#include "SelfBuff.h"

class ImprovedAspectOfTheHawkBuff: public SelfBuff {
public:
    ImprovedAspectOfTheHawkBuff(Character* pchar);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
