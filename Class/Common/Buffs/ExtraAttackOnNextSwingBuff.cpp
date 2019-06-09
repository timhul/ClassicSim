#include "ExtraAttackOnNextSwingBuff.h"

#include "ExtraAttackInstantProc.h"

ExtraAttackOnNextSwingBuff::ExtraAttackOnNextSwingBuff(Character* pchar,
                                                       ExtraAttackInstantProc* extra_attack,
                                                       const int num_attacks):
    SelfBuff(pchar, "ExtraAttackOnSwing", NO_ICON, BuffDuration::PERMANENT, num_attacks),
    extra_attack(extra_attack)
{
    this->hidden = true;
}

void ExtraAttackOnNextSwingBuff::buff_effect_when_applied() {
    extra_attack->enable_proc();
}

void ExtraAttackOnNextSwingBuff::buff_effect_when_removed() {
    extra_attack->disable_proc();
}
