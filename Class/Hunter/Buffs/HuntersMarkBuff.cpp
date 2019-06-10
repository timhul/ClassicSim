#include "HuntersMarkBuff.h"

#include "CharacterStats.h"
#include "Hunter.h"

HuntersMarkBuff::HuntersMarkBuff(Character* pchar):
    SharedDebuff(pchar->get_raid_control(), "Hunter's Mark", "Assets/ability/Ability_hunter_snipershot.png", 120, 0)
{}

void HuntersMarkBuff::buff_effect_when_applied() {
    pchar->get_stats()->increase_ranged_ap(ap_bonus);
}

void HuntersMarkBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_ranged_ap(ap_bonus);
}
