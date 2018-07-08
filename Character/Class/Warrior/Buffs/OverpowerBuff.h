#ifndef OVERPOWERBUFF_H
#define OVERPOWERBUFF_H

#include "Buff.h"

class OverpowerBuff: public Buff {
public:
    OverpowerBuff(Character* pchar);

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

protected:
private:

};


#endif // OVERPOWERBUFF_H
