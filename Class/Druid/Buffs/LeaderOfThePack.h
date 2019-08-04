#pragma once

#include "PartyBuff.h"

class Druid;

class LeaderOfThePack: public PartyBuff {
public:
    LeaderOfThePack(Druid* pchar);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
