#ifndef FAERIEFIREBUFF_H
#define FAERIEFIREBUFF_H

#include "ExternalBuff.h"

class FaerieFireBuff: public ExternalBuff {
public:
    FaerieFireBuff(Character* pchar);

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

protected:
private:

};

#endif // FAERIEFIREBUFF_H
