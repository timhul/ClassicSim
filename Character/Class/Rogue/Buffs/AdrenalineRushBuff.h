#ifndef ADRENALINERUSHBUFF_H
#define ADRENALINERUSHBUFF_H

#include "Buff.h"

class Rogue;

class AdrenalineRushBuff: public Buff {
public:
    AdrenalineRushBuff(Character* pchar);
    ~AdrenalineRushBuff() override;

private:
    Rogue* rogue;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};

#endif // ADRENALINERUSHBUFF_H
