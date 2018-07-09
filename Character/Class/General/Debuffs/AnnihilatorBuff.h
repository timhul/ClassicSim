#ifndef ANNIHILATORBUFF_H
#define ANNIHILATORBUFF_H

#include "ExternalBuff.h"

class AnnihilatorBuff: public ExternalBuff {
public:
    AnnihilatorBuff(Character* pchar);

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

protected:
private:

};

#endif // ANNIHILATORBUFF_H
