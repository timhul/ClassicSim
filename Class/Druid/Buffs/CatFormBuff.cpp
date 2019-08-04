#include "CatFormBuff.h"

#include "CharacterStats.h"
#include "Druid.h"
#include "Equipment.h"

CatFormBuff::CatFormBuff(Druid* pchar):
    SelfBuff(pchar, "Cat Form", "Assets/spell/Spell_nature_ravenform.png",  BuffDuration::PERMANENT, 0),
    TalentRequirer({
                   new TalentRequirerInfo("Sharpened Claws", 3, DisabledAtZero::No),
                   }),
    druid(pchar)
{}

void CatFormBuff::buff_effect_when_applied() {
    pchar->get_equipment()->druid_cat_form_switch_to_claws();

    if (sharpened_claws_bonus > 0)
        druid->get_stats()->increase_melee_crit(sharpened_claws_bonus);
}

void CatFormBuff::buff_effect_when_removed() {
    pchar->get_equipment()->druid_switch_to_normal_weapon();

    if (sharpened_claws_bonus > 0)
        druid->get_stats()->decrease_melee_crit(sharpened_claws_bonus);
}

void CatFormBuff::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Sharpened Claws") {
        if (is_active() && curr > 1)
            druid->get_stats()->decrease_melee_crit(sharpened_claws_bonus);

        sharpened_claws_bonus = sharpened_claws_ranks[curr];

        if (is_active())
            druid->get_stats()->increase_melee_crit(sharpened_claws_bonus);
    }
}

void CatFormBuff::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Sharpened Claws") {
        if (is_active())
            druid->get_stats()->decrease_melee_crit(sharpened_claws_bonus);

        sharpened_claws_bonus = sharpened_claws_ranks[curr];

        if (is_active() && sharpened_claws_bonus > 0)
            druid->get_stats()->increase_melee_crit(sharpened_claws_bonus);
    }
}
