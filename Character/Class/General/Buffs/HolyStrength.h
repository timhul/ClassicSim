#ifndef HOLYSTRENGTH_H
#define HOLYSTRENGTH_H

#include "Buff.h"

class HolyStrength: public Buff {
public:
    HolyStrength(Character* pchar):
        Buff(pchar, "Holy Strength", 15, 0)
    {}

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

protected:
private:
};

#endif // HOLYSTRENGTH_H
