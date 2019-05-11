#include "ExposeWeaknessBuff.h"

#include "Character.h"
#include "CharacterStats.h"

ExposeWeaknessBuff::ExposeWeaknessBuff(Character* pchar):
    Buff(pchar, "Expose Weakness", "Assets/ability/Ability_hunter_snipershot.png", 7.0, 0)
{}

void ExposeWeaknessBuff::buff_effect_when_applied() {
    pchar->get_stats()->increase_ranged_ap(450);
}

void ExposeWeaknessBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_ranged_ap(450);
}
