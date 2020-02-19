#pragma once

#include "SelfBuff.h"

class Rogue;

class BladeFlurryBuff : public SelfBuff {
public:
    BladeFlurryBuff(Rogue* rogue);
    ~BladeFlurryBuff() override;

private:
    Rogue* rogue;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
