#ifndef BATTLESHOUTBUFF_H
#define BATTLESHOUTBUFF_H

#include "PartyBuff.h"
#include "TalentRequirer.h"

#include <QVector>

class BattleShoutBuff: public PartyBuff {
public:
    BattleShoutBuff(Character* pchar);

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

private:
    friend class BattleShout;

    unsigned attack_power;
};

#endif // BATTLESHOUTBUFF_H
