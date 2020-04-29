#pragma once

#include "SelfBuff.h"

class Mage;
class Mana;

class MageArmorBuff : public SelfBuff {
public:
    MageArmorBuff(Mage* mage);

private:
    Mana* mana;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
