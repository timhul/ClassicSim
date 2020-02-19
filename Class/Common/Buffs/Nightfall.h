#pragma once

#include "SharedDebuff.h"

class Nightfall : public SharedDebuff {
public:
    Nightfall(Character* pchar);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
