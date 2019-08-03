#pragma once

#include "SelfBuff.h"

class Druid;

class CatFormBuff: public SelfBuff {
public:
    CatFormBuff(Druid* pchar);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
