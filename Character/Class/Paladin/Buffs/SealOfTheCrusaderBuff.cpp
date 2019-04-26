#include "SealOfTheCrusaderBuff.h"

#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "MainhandAttackPaladin.h"
#include "Paladin.h"
#include "PaladinSpells.h"

SealOfTheCrusaderBuff::SealOfTheCrusaderBuff(Paladin* pchar):
    Buff(pchar, "Seal of the Crusader", "Assets/spell/Spell_holy_holysmite.png", 30, 0),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Improved Seal of the Crusader", 3, DisabledAtZero::No)}),
    paladin(dynamic_cast<Paladin*>(pchar))
{
    sotc_ap_bonus = sotc_ap_base;
}

void SealOfTheCrusaderBuff::buff_effect_when_applied() {
    pchar->get_stats()->increase_melee_ap(sotc_ap_bonus);
    pchar->get_stats()->increase_melee_attack_speed(40);
    dynamic_cast<MainhandAttackPaladin*>(pchar->get_spells()->get_mh_attack())->apply_seal_of_the_crusader_penalty();
}

void SealOfTheCrusaderBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_melee_ap(sotc_ap_bonus);
    pchar->get_stats()->decrease_melee_attack_speed(40);
    dynamic_cast<MainhandAttackPaladin*>(pchar->get_spells()->get_mh_attack())->remove_seal_of_the_crusader_penalty();
}

void SealOfTheCrusaderBuff::increase_talent_rank_effect(const QString&, const int curr) {
    sotc_ap_bonus = static_cast<unsigned>(round(sotc_ap_base * improved_sotc_ranks[curr]));;
}

void SealOfTheCrusaderBuff::decrease_talent_rank_effect(const QString&, const int curr) {
    sotc_ap_bonus = static_cast<unsigned>(round(sotc_ap_base * improved_sotc_ranks[curr]));;
}
