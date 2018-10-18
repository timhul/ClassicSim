#ifndef HOLYSTRENGTH_H
#define HOLYSTRENGTH_H

#include "Buff.h"

class HolyStrength: public Buff {
public:
    HolyStrength(Character* pchar, const QString& weapon_side);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};

#endif // HOLYSTRENGTH_H
