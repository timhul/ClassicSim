#ifndef EXPOSEWEAKNESSBUFF_H
#define EXPOSEWEAKNESSBUFF_H

#include "SharedDebuff.h"

class ExposeWeaknessBuff: public SharedDebuff {
public:
    ExposeWeaknessBuff(Character* pchar);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};

#endif // EXPOSEWEAKNESSBUFF_H
