#ifndef DEATHWISHBUFF_H
#define DEATHWISHBUFF_H

#include "Buff.h"
#include "TalentRequirer.h"

class DeathWishBuff: public Buff {
public:
    DeathWishBuff(Character* pchar);
    ~DeathWishBuff() override;

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};

#endif // DEATHWISHBUFF_H
