#pragma once

#include "SelfBuff.h"

class ArmorPenetrationBuff : public SelfBuff {
public:
    ArmorPenetrationBuff(Character* pchar, const QString& name, const QString& icon, const int reduction, const int max_stacks, const int duration);

private:
    int current_stacks;
    int max_stacks;
    int reduction_per_stack;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
    void buff_effect_when_refreshed() override;
};
