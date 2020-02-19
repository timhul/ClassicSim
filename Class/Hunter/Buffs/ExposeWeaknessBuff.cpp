#include "ExposeWeaknessBuff.h"

#include "Character.h"
#include "Stats.h"
#include "Target.h"

ExposeWeaknessBuff::ExposeWeaknessBuff(Character* pchar) :
    SharedDebuff(pchar, "Expose Weakness", "Assets/ability/Ability_hunter_snipershot.png", Priority::Low, 7.0, 0) {}

void ExposeWeaknessBuff::buff_effect_when_applied() {
    pchar->get_target()->get_stats()->increase_base_ranged_ap(450);
}

void ExposeWeaknessBuff::buff_effect_when_removed() {
    pchar->get_target()->get_stats()->decrease_base_ranged_ap(450);
}
