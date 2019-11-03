#pragma once

#include "PartyBuff.h"

class Paladin;

class SanctityAuraBuff: public PartyBuff {
public:
    SanctityAuraBuff(Paladin* paladin);
    ~SanctityAuraBuff() override = default;

private:
    Paladin* paladin;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
