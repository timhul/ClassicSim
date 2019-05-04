#ifndef BATTLESTANCEBUFF_H
#define BATTLESTANCEBUFF_H

#include "Buff.h"

class BattleStanceBuff: public Buff {
public:
    BattleStanceBuff(Character* pchar);

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};

#endif // BATTLESTANCEBUFF_H
