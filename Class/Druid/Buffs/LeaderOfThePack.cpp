#include "LeaderOfThePack.h"

#include "CharacterStats.h"
#include "Druid.h"

LeaderOfThePack::LeaderOfThePack(Druid* pchar) :
    PartyBuff(pchar, "Leader of the Pack", "Assets/spell/Spell_nature_unyeildingstamina.png", BuffDuration::PERMANENT, 0) {}

void LeaderOfThePack::buff_effect_when_applied() {
    pchar->get_stats()->increase_melee_aura_crit(300);
    pchar->get_stats()->increase_ranged_crit(300);
}

void LeaderOfThePack::buff_effect_when_removed() {
    pchar->get_stats()->decrease_melee_aura_crit(300);
    pchar->get_stats()->decrease_ranged_crit(300);
}
