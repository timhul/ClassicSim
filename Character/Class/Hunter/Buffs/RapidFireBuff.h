#ifndef RAPIDFIREBUFF_H
#define RAPIDFIREBUFF_H

#include "Buff.h"

class RapidFireBuff: public Buff {
public:
    RapidFireBuff(Character* pchar);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};

#endif // RAPIDFIREBUFF_H
