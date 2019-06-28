#pragma once

#include "SharedBuff.h"

class FelstrikerBuff: public SharedBuff {
public:
    FelstrikerBuff(Character* pchar, const int duration);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

    void set_tables_for_guaranteed_hit(const int);
};
