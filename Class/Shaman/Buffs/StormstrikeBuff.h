#pragma once

#include "SharedDebuff.h"

class StormstrikeBuff : public SharedDebuff {
public:
    StormstrikeBuff(Character* pchar);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
