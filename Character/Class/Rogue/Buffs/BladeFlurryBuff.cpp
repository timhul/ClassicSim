#include "BladeFlurryBuff.h"

#include "Energy.h"
#include "Rogue.h"

BladeFlurryBuff::BladeFlurryBuff(Character* pchar):
    Buff(pchar, "Blade Flurry", "Assets/ability/Ability_warrior_punishingblow.png", 15, 0),
    rogue(dynamic_cast<Rogue*>(pchar))
{}

BladeFlurryBuff::~BladeFlurryBuff() {
    if (is_enabled())
        disable_buff();
}

void BladeFlurryBuff::buff_effect_when_applied() {
    rogue->increase_melee_attack_speed(20);
}

void BladeFlurryBuff::buff_effect_when_removed() {
    rogue->decrease_melee_attack_speed(20);
}
