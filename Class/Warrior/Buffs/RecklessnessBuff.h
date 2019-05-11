#ifndef RECKLESSNESSBUFF_H
#define RECKLESSNESSBUFF_H

#include "Buff.h"

class RecklessnessBuff: public Buff {
public:
    RecklessnessBuff(Character* pchar);

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

private:
};

#endif // RECKLESSNESSBUFF_H
