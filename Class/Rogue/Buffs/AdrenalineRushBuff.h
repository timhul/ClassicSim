#pragma once

#include "SelfBuff.h"

class Rogue;

class AdrenalineRushBuff: public SelfBuff {
public:
    AdrenalineRushBuff(Rogue* rogue);
    ~AdrenalineRushBuff() override;

private:
    Rogue* rogue;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
