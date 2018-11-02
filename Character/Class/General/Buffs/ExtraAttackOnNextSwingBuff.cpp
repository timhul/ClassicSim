#include "Character.h"
#include "EnabledBuffs.h"
#include "EnabledProcs.h"
#include "ExtraAttackInstantProc.h"
#include "ExtraAttackOnNextSwingBuff.h"

ExtraAttackOnNextSwingBuff::ExtraAttackOnNextSwingBuff(Character* pchar,
                                                       ExtraAttackInstantProc* extra_attack,
                                                       const int num_attacks):
    Buff(pchar, "ExtraAttackOnSwing", NO_ICON, BuffDuration::PERMANENT, num_attacks),
    extra_attack(extra_attack)
{}

void ExtraAttackOnNextSwingBuff::buff_effect_when_applied() {
    pchar->get_enabled_procs()->add_proc_effect(extra_attack);
}

void ExtraAttackOnNextSwingBuff::buff_effect_when_removed() {
    pchar->get_enabled_procs()->remove_proc_effect(extra_attack->get_instance_id());
}
