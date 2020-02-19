#pragma once

#include "SelfBuff.h"

enum AffectedWeaponSide
{
    Mainhand = 0,
    Offhand,
    Ranged,
    All
};

class FlatWeaponDamageBuff : public SelfBuff {
public:
    FlatWeaponDamageBuff(Character* pchar,
                         const QString& name,
                         const QString& icon,
                         const int duration,
                         const int base_charges,
                         const AffectedWeaponSide wpn_side,
                         const unsigned bonus);

private:
    const AffectedWeaponSide wpn_side;
    const unsigned bonus;
    unsigned active_bonus;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
    void charge_change_effect() override;
};
