#pragma once

#include "SelfBuff.h"

class DevilsaurEye: public SelfBuff {
public:
    DevilsaurEye(Character* pchar);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
