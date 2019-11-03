#pragma once

#include "SelfBuff.h"

class Mage;
class Mana;

class EvocationBuff: public SelfBuff {
public:
    EvocationBuff(Mage* mage);

private:
    Mana* mana;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
