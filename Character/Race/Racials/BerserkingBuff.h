#ifndef BERSERKINGBUFF_H
#define BERSERKINGBUFF_H

#include "Buff.h"

class Random;

class BerserkingBuff: public Buff {
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
