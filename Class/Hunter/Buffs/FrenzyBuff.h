#pragma once

#include "SelfBuff.h"

class Pet;

class FrenzyBuff: public SelfBuff {
public:
    FrenzyBuff(Character* pchar, Pet* pet);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
