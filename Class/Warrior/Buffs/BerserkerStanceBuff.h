#ifndef BERSERKERSTANCEBUFF_H
#define BERSERKERSTANCEBUFF_H

#include "SelfBuff.h"

class Warrior;

class BerserkerStanceBuff: public SelfBuff {
public:
    BerserkerStanceBuff(Character* pchar);

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

private:
    Warrior* warr;
};

#endif // BERSERKERSTANCEBUFF_H
