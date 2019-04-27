#include "JudgementOfTheCrusader.h"

#include "CharacterStats.h"
#include "Paladin.h"

JudgementOfTheCrusader::JudgementOfTheCrusader(Paladin* pchar):
    Buff(pchar, "Judgement of the Crusader", "Assets/spell/Spell_holy_holysmite.png", 10, 0),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Improved Seal of the Crusader", 3, DisabledAtZero::No)}),
    paladin(dynamic_cast<Paladin*>(pchar))
{
    this->debuff = true;
    this->holy_damage_bonus = holy_damage_base;
}

void JudgementOfTheCrusader::buff_effect_when_applied() {
    pchar->get_stats()->increase_spell_damage_vs_school(holy_damage_bonus, MagicSchool::Holy);
}

void JudgementOfTheCrusader::buff_effect_when_removed() {
    pchar->get_stats()->decrease_spell_damage_vs_school(holy_damage_bonus, MagicSchool::Holy);
}

void JudgementOfTheCrusader::increase_talent_rank_effect(const QString&, const int curr) {
    holy_damage_bonus = static_cast<unsigned>(round(holy_damage_base * improved_sotc_ranks[curr]));
}

void JudgementOfTheCrusader::decrease_talent_rank_effect(const QString&, const int curr) {
    holy_damage_bonus = static_cast<unsigned>(round(holy_damage_base * improved_sotc_ranks[curr]));
}
