#ifndef BERSERKINGBUFF_H
#define BERSERKINGBUFF_H

#include "SelfBuff.h"

class Random;

class BerserkingBuff: public SelfBuff {
public:
    BerserkingBuff(Character* pchar);
    ~BerserkingBuff() override;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

private:
    Random* random;
    unsigned curr_buff;
};

#endif // BERSERKINGBUFF_H
