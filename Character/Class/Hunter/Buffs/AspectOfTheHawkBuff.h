#ifndef ASPECTOFTHEHAWKBUFF_H
#define ASPECTOFTHEHAWKBUFF_H

#include "Buff.h"

class AspectOfTheHawkBuff: public Buff {
public:
    AspectOfTheHawkBuff(Character* pchar);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};

#endif // ASPECTOFTHEHAWKBUFF_H
