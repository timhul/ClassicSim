#ifndef ARMORPENETRATIONBUFF_H
#define ARMORPENETRATIONBUFF_H

#include "Buff.h"

class ArmorPenetrationBuff: public Buff {
public:
    ArmorPenetrationBuff(Character* pchar, const QString& name, const int reduction, const int max_stacks, const int duration);

private:
    int current_stacks;
    int max_stacks;
    int reduction_per_stack;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
    void buff_effect_when_refreshed() override;
};

#endif // ARMORPENETRATIONBUFF_H
