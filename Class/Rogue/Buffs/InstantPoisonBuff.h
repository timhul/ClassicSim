#pragma once

#include "UniqueDebuff.h"

class InstantPoison;

class InstantPoisonBuff: public UniqueDebuff {
public:
    InstantPoisonBuff(Character* pchar, InstantPoison* instant_poison_proc, const QString& weapon_side);

private:
    InstantPoison* instant_poison_proc;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
