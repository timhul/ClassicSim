#ifndef DEFENSIVESTANCEBUFF_H
#define DEFENSIVESTANCEBUFF_H

#include "SelfBuff.h"

class Warrior;

class DefensiveStanceBuff: public SelfBuff {
public:
    DefensiveStanceBuff(Character* pchar);

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

private:
    Warrior* warr;
};

#endif // DEFENSIVESTANCEBUFF_H
