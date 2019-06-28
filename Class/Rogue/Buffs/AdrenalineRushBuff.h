#pragma once

#include "SelfBuff.h"

class Rogue;

class AdrenalineRushBuff: public SelfBuff {
public:
    AdrenalineRushBuff(Character* pchar);
    ~AdrenalineRushBuff() override;

private:
    Rogue* rogue;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
