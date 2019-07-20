#pragma once

#include "SharedDebuff.h"

class Character;

class WintersChill: public SharedDebuff {
public:
    WintersChill(Character* pchar);

private:
    const unsigned increment {200};
    unsigned current_increment {0};

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
    void buff_effect_when_refreshed() override;
};
