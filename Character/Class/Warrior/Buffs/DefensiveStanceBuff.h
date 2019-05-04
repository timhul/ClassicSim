#ifndef DEFENSIVESTANCEBUFF_H
#define DEFENSIVESTANCEBUFF_H

#include "Buff.h"

class Warrior;

class DefensiveStanceBuff: public Buff {
public:
    DefensiveStanceBuff(Character* pchar);

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

private:
    Warrior* warr;
};

#endif // DEFENSIVESTANCEBUFF_H
