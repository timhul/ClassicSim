#include "ImprovedShadowBolt.h"

#include "Character.h"
#include "Stats.h"
#include "Target.h"

ImprovedShadowBolt::ImprovedShadowBolt(Character* pchar_) :
    SharedDebuff(pchar_, "Improved Shadow Bolt", "Assets/spell/Spell_shadow_shadowbolt.png", Priority::Mid, 12, 4) {}

void ImprovedShadowBolt::buff_effect_when_applied() {
    pchar->get_target()->increase_magic_school_damage_mod(20, MagicSchool::Shadow);
}

void ImprovedShadowBolt::buff_effect_when_removed() {
    pchar->get_target()->decrease_magic_school_damage_mod(20, MagicSchool::Shadow);
}
