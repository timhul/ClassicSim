#pragma once

#include "SelfBuff.h"

class RecklessnessBuff: public SelfBuff {
public:
    RecklessnessBuff(Character* pchar);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
