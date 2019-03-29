#ifndef IMPROVEDASPECTOFTHEHAWKBUFF_H
#define IMPROVEDASPECTOFTHEHAWKBUFF_H

#include "Buff.h"

class ImprovedAspectOfTheHawkBuff: public Buff {
public:
    ImprovedAspectOfTheHawkBuff(Character* pchar);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};

#endif // IMPROVEDASPECTOFTHEHAWKBUFF_H
