#include "HuntersMarkBuff.h"

#include "CharacterStats.h"
#include "Hunter.h"

HuntersMarkBuff::HuntersMarkBuff(Character* pchar):
    SharedDebuff(pchar->get_raid_control(), "Hunter's Mark", "Assets/ability/Ability_hunter_snipershot.png", 120, 0),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Improved Hunter's Mark", 5, DisabledAtZero::No)}),
    base_ranged_ap_bonus(110)
{
    hunters_mark_bonus = base_ranged_ap_bonus;
    imp_hunters_mark_ranks = {
        1.0, 1.03, 1.06, 1.09, 1.12, 1.15
    };
}

void HuntersMarkBuff::buff_effect_when_applied() {
    pchar->get_stats()->increase_ranged_ap(hunters_mark_bonus);
}

void HuntersMarkBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_ranged_ap(hunters_mark_bonus);
}

void HuntersMarkBuff::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Hunter's Mark")
        hunters_mark_bonus = static_cast<unsigned>(round(static_cast<double>(base_ranged_ap_bonus) * imp_hunters_mark_ranks[curr]));
}

void HuntersMarkBuff::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Hunter's Mark")
        hunters_mark_bonus = static_cast<unsigned>(round(static_cast<double>(base_ranged_ap_bonus) * imp_hunters_mark_ranks[curr]));
}
