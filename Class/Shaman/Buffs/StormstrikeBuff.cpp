#include "StormstrikeBuff.h"

#include "Character.h"
#include "CharacterStats.h"

StormstrikeBuff::StormstrikeBuff(Character* pchar):
    Buff(pchar, "Stormstrike", "Assets/spell/Spell_holy_sealofmight.png", 12, 2)
{}

void StormstrikeBuff::buff_effect_when_applied() {
    pchar->get_stats()->increase_spell_dmg_mod(20, MagicSchool::Nature, this);
}

void StormstrikeBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_spell_dmg_mod(20, MagicSchool::Nature, this);
}
