#ifndef BLOODFURYBUFF_H
#define BLOODFURYBUFF_H

#include "Buff.h"

class BloodFuryBuff: public Buff {
public:
    BloodFuryBuff(Character* pchar): Buff(pchar, "Blood Fury", 15, 1)
    {}

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

protected:
private:
};

#endif // BLOODFURYBUFF_H
