#pragma once

#include "Buff.h"

class StormstrikeBuff: public Buff {
public:
    StormstrikeBuff(Character* pchar);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
