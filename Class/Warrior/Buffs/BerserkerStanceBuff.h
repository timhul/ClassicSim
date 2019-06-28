#pragma once

#include "SelfBuff.h"

class Warrior;

class BerserkerStanceBuff: public SelfBuff {
public:
    BerserkerStanceBuff(Character* pchar);

private:
    Warrior* warr;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
