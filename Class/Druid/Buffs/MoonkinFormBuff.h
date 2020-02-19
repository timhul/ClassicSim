#pragma once

#include "PartyBuff.h"

class Druid;

class MoonkinFormBuff : public PartyBuff {
public:
    MoonkinFormBuff(Druid* pchar);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
