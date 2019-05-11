#include "InstantPoisonBuff.h"

#include "InstantPoison.h"

InstantPoisonBuff::InstantPoisonBuff(Character* pchar, InstantPoison* instant_poison_proc, const QString& weapon_side):
    Buff(pchar, "Instant Poison " + weapon_side, "Assets/ability/Ability_poisons.png", 1800, 115),
    instant_poison_proc(instant_poison_proc)
{
    hidden = true;
}

void InstantPoisonBuff::buff_effect_when_applied() {
    instant_poison_proc->enable_proc();
}

void InstantPoisonBuff::buff_effect_when_removed() {
    instant_poison_proc->disable_proc();
}
