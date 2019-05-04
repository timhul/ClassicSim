#include "SealOfTheCrusaderBuff.h"

#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "MainhandAttackPaladin.h"
#include "Paladin.h"
#include "PaladinSpells.h"
#include "Utils/Check.h"

SealOfTheCrusaderBuff::SealOfTheCrusaderBuff(Paladin* pchar):
    Buff(pchar, "Seal of the Crusader", "Assets/spell/Spell_holy_holysmite.png", 30, 0),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Improved Seal of the Crusader", 3, DisabledAtZero::No)}),
    ItemModificationRequirer({22401, 23203}),
    paladin(dynamic_cast<Paladin*>(pchar))
{}

void SealOfTheCrusaderBuff::buff_effect_when_applied() {
    pchar->get_stats()->increase_melee_ap(static_cast<unsigned>(round((sotc_ap_base + libram_of_fervor_bonus) * improved_sotc_mod)));
    pchar->get_stats()->increase_melee_attack_speed(40);
    dynamic_cast<MainhandAttackPaladin*>(pchar->get_spells()->get_mh_attack())->apply_seal_of_the_crusader_penalty();
}

void SealOfTheCrusaderBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_melee_ap(static_cast<unsigned>(round((sotc_ap_base + libram_of_fervor_bonus) * improved_sotc_mod)));
    pchar->get_stats()->decrease_melee_attack_speed(40);
    dynamic_cast<MainhandAttackPaladin*>(pchar->get_spells()->get_mh_attack())->remove_seal_of_the_crusader_penalty();
}

void SealOfTheCrusaderBuff::increase_talent_rank_effect(const QString&, const int curr) {
    improved_sotc_mod = improved_sotc_ranks[curr];
}

void SealOfTheCrusaderBuff::decrease_talent_rank_effect(const QString&, const int curr) {
    improved_sotc_mod = improved_sotc_ranks[curr];
}

void SealOfTheCrusaderBuff::activate_item_effect(const int item_id) {
    switch (item_id) {
    case 22401:
        break;
    case 23203:
        libram_of_fervor_bonus = 48;
        break;
    default:
        check(false, "SealOfTheCrusaderBuff::activate_item_effect reached end of switch");
    }
}

void SealOfTheCrusaderBuff::deactivate_item_effect(const int item_id) {
    switch (item_id) {
    case 22401:
        break;
    case 23203:
        libram_of_fervor_bonus = 0;
        break;
    default:
        check(false, "SealOfTheCrusaderBuff::deactivate_item_effect reached end of switch");
    }
}
