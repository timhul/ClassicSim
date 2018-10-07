#ifndef DEATHWISHBUFF_H
#define DEATHWISHBUFF_H

#include "Buff.h"

class DeathWishBuff: public Buff {
public:
    DeathWishBuff(Character* pchar): Buff(pchar, "Death Wish", 30, 0)
    {}

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

protected:
private:
};

#endif // DEATHWISHBUFF_H
