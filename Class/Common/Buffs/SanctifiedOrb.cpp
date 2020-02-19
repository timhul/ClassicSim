#include "SanctifiedOrb.h"

#include "Character.h"
#include "CharacterStats.h"

SanctifiedOrb::SanctifiedOrb(Character* pchar) : SelfBuff(pchar, "Sanctified Orb", "Assets/items/Inv_misc_gem_pearl_04.png", 25, 0) {}

void SanctifiedOrb::buff_effect_when_applied() {
    pchar->get_stats()->increase_melee_aura_crit(300);
    pchar->get_stats()->increase_spell_crit(300);
}

void SanctifiedOrb::buff_effect_when_removed() {
    pchar->get_stats()->decrease_melee_aura_crit(300);
    pchar->get_stats()->decrease_spell_crit(300);
}
