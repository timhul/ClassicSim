#include "HuntersMarkBuff.h"

#include "Hunter.h"
#include "Stats.h"
#include "Target.h"

HuntersMarkBuff::HuntersMarkBuff(Character* pchar):
    SharedDebuff(pchar, "Hunter's Mark", "Assets/ability/Ability_hunter_snipershot.png", 120, 0)
{}

void HuntersMarkBuff::buff_effect_when_applied() {
    pchar->get_target()->get_stats()->increase_base_ranged_ap(ap_bonus);
}

void HuntersMarkBuff::buff_effect_when_removed() {
    pchar->get_target()->get_stats()->decrease_base_ranged_ap(ap_bonus);
}
