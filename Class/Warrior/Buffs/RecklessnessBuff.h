#ifndef RECKLESSNESSBUFF_H
#define RECKLESSNESSBUFF_H

#include "SelfBuff.h"

class RecklessnessBuff: public SelfBuff {
public:
    RecklessnessBuff(Character* pchar);

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

private:
};

#endif // RECKLESSNESSBUFF_H
