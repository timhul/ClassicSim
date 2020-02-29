#pragma once

#include "SharedDebuff.h"

class Character;

class ImprovedShadowBolt : public SharedDebuff {
public:
    ImprovedShadowBolt(Character* pchar);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
