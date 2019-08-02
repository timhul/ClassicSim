#include "MoonkinFormBuff.h"

#include "CharacterStats.h"
#include "Druid.h"

MoonkinFormBuff::MoonkinFormBuff(Druid* pchar):
    PartyBuff(pchar, "Moonkin Form", "Assets/spell/Spell_nature_forceofnature.png",  BuffDuration::PERMANENT, 0)
{}

void MoonkinFormBuff::buff_effect_when_applied() {
    pchar->get_stats()->increase_spell_crit(300);
}

void MoonkinFormBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_spell_crit(300);
}
