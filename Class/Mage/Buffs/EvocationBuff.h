#pragma once

#include "SelfBuff.h"

class Character;
class Mana;

class EvocationBuff: public SelfBuff {
public:
    EvocationBuff(Character* pchar);

private:
    class Mana* mana;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
