#ifndef NOEFFECTBUFF_H
#define NOEFFECTBUFF_H

#include "Buff.h"

class NoEffectBuff: public Buff {
public:
    NoEffectBuff(Character* pchar,
                 const int duration);

    void link_buff_expiration(Buff* buff_to_cancel);

private:
    Buff* linked_buff;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};

#endif // NOEFFECTBUFF_H
