#ifndef HEROICSTRIKEBUFF_H
#define HEROICSTRIKEBUFF_H

#include "Buff.h"

class HeroicStrikeBuff: public Buff {
public:
    HeroicStrikeBuff(Character* pchar): Buff(pchar, "Heroic Strike Buff",
                                             BuffDuration::PERMANENT, 1) {
        hidden = true;
    }

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

protected:
private:

};

#endif // HEROICSTRIKEBUFF_H
