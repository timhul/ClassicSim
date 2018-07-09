#ifndef SUNDERARMORBUFF_H
#define SUNDERARMORBUFF_H

#include "ExternalBuff.h"

class SunderArmorBuff: public ExternalBuff {
public:
    SunderArmorBuff(Character* pchar);

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

protected:
private:

};

#endif // SUNDERARMORBUFF_H
