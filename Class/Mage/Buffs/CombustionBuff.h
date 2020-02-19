#pragma once

#include "SelfBuff.h"

class Character;

class CombustionBuff : public SelfBuff {
public:
    CombustionBuff(Character* pchar);

private:
    const unsigned increment {1000};
    unsigned current_increment {0};

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
    void buff_effect_when_refreshed() override;
};
