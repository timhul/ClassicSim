#pragma once

#include "SelfBuff.h"

class Warrior;

class BattleStanceBuff : public SelfBuff {
public:
    BattleStanceBuff(Warrior* warrior);

private:
    Warrior* warrior;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
