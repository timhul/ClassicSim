#ifndef FRENZYBUFF_H
#define FRENZYBUFF_H

#include "Buff.h"

class Pet;

class FrenzyBuff: public Buff {
public:
    FrenzyBuff(Character* pchar, Pet* pet);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};

#endif // FRENZYBUFF_H
