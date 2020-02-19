#pragma once

#include "SelfBuff.h"

class ZandalarianHeroCharm : public SelfBuff {
public:
    ZandalarianHeroCharm(Character* pchar);

private:
    const unsigned max_spell_damage {204};
    unsigned spell_damage {0};

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
    void charge_change_effect() override;
};
