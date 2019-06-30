#include "CombustionBuff.h"

#include "Character.h"
#include "CharacterStats.h"

CombustionBuff::CombustionBuff(Character* pchar):
    SelfBuff(pchar, "Combustion", "Assets/spell/Spell_fire_sealoffire.png", BuffDuration::PERMANENT, 3)
{}

void CombustionBuff::buff_effect_when_applied() {
    current_increment += increment;
    pchar->get_stats()->increase_spell_crit(MagicSchool::Fire, increment);
}

void CombustionBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_spell_crit(MagicSchool::Fire, current_increment);

    current_increment = 0;
}

void CombustionBuff::buff_effect_when_refreshed() {
    buff_effect_when_applied();
}
