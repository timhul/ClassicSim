#pragma once

#include "SelfBuff.h"
#include "TalentRequirer.h"

class DeathWishBuff : public SelfBuff {
public:
    DeathWishBuff(Character* pchar);
    ~DeathWishBuff() override;

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
