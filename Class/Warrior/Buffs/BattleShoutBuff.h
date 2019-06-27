#pragma once

#include "PartyBuff.h"

#include <QVector>

class Warrior;

class BattleShoutBuff: public PartyBuff {
public:
    BattleShoutBuff(Warrior* pchar);

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

private:
    friend class BattleShout;

    unsigned attack_power {0};
};
