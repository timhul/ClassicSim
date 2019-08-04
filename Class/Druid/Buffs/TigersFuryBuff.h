#pragma once

#include "SelfBuff.h"

class TigersFuryBuff: public SelfBuff{
public:
    TigersFuryBuff(Character* pchar);

private:
    friend class TigersFury;

    unsigned flat_damage_bonus {10};

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
