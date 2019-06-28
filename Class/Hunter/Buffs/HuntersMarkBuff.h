#pragma once

#include "SharedDebuff.h"

#include <QVector>

class HuntersMarkBuff: public SharedDebuff {
public:
    HuntersMarkBuff(Character* pchar);

private:
    friend class HuntersMark;

    unsigned ap_bonus {0};

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

};
