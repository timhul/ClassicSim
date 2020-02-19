#include "JudgementOfTheCrusader.h"

#include <cmath>

#include "Paladin.h"
#include "Stats.h"
#include "Target.h"
#include "Utils/Check.h"

JudgementOfTheCrusader::JudgementOfTheCrusader(Paladin* pchar) :
    SharedDebuff(pchar, "Judgement of the Crusader", "Assets/spell/Spell_holy_holysmite.png", Priority::Mid, 10, 0),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo("Improved Seal of the Crusader", 3, DisabledAtZero::No)}),
    ItemModificationRequirer({16471, 23274, 23203}) {}

void JudgementOfTheCrusader::buff_effect_when_applied() {
    pchar->get_target()->get_stats()->increase_spell_damage_vs_school(static_cast<unsigned>(
                                                                          round((holy_damage_base + pvp_glove_bonus + libram_of_fervor_bonus)
                                                                                * improved_sotc_mod)),
                                                                      MagicSchool::Holy);
}

void JudgementOfTheCrusader::buff_effect_when_removed() {
    pchar->get_target()->get_stats()->decrease_spell_damage_vs_school(static_cast<unsigned>(
                                                                          round((holy_damage_base + pvp_glove_bonus + libram_of_fervor_bonus)
                                                                                * improved_sotc_mod)),
                                                                      MagicSchool::Holy);
}

void JudgementOfTheCrusader::increase_talent_rank_effect(const QString&, const int curr) {
    improved_sotc_mod = improved_sotc_ranks[curr];
}

void JudgementOfTheCrusader::decrease_talent_rank_effect(const QString&, const int curr) {
    improved_sotc_mod = improved_sotc_ranks[curr];
}

void JudgementOfTheCrusader::activate_item_effect(const int item_id) {
    switch (item_id) {
    case 16471:
    case 23274:
        pvp_glove_bonus = 20;
        break;
    case 23203:
        libram_of_fervor_bonus = 33;
        break;
    default:
        check(false, "JudgementOfTheCrusader::activate_item_effect reached end of switch");
    }
}

void JudgementOfTheCrusader::deactivate_item_effect(const int item_id) {
    switch (item_id) {
    case 16471:
    case 23274:
        pvp_glove_bonus = 0;
        break;
    case 23203:
        libram_of_fervor_bonus = 0;
        break;
    default:
        check(false, "JudgementOfTheCrusader::deactivate_item_effect reached end of switch");
    }
}
