#ifndef EXTRAATTACKONSWING_H
#define EXTRAATTACKONSWING_H

#include "SelfBuff.h"

class ExtraAttackInstantProc;

class ExtraAttackOnNextSwingBuff: public SelfBuff {
public:
    ExtraAttackOnNextSwingBuff(Character* pchar, ExtraAttackInstantProc* extra_attack,
                               const int num_attacks);

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

protected:
private:
    ExtraAttackInstantProc* extra_attack;
};

#endif // EXTRAATTACKONSWING_H
