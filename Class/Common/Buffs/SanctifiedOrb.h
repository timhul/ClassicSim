#pragma once

#include "SelfBuff.h"

class SanctifiedOrb: public SelfBuff {
public:
    SanctifiedOrb(Character* pchar);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
