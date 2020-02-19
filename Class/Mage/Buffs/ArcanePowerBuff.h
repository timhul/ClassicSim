#pragma once

#include <QVector>

#include "SelfBuff.h"

class Character;

class ArcanePowerBuff : public SelfBuff {
public:
    ArcanePowerBuff(Character* pchar);

private:
    const QVector<QString> affected_spells;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
