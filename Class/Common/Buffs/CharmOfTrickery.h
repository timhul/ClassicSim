#pragma once

#include "SelfBuff.h"

class CharmOfTrickery : public SelfBuff {
public:
    CharmOfTrickery(Character* pchar);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
