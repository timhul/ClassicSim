#ifndef BLOODFURYBUFF_H
#define BLOODFURYBUFF_H

#include "SelfBuff.h"

class BloodFuryBuff: public SelfBuff {
public:
    BloodFuryBuff(Character* pchar): SelfBuff(pchar, "Blood Fury", "Assets/races/Racial_orc_berserkerstrength.png", 15, 1)
    {}

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

protected:
private:
};

#endif // BLOODFURYBUFF_H
