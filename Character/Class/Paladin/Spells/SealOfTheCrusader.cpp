#include "SealOfTheCrusader.h"

#include "JudgementOfTheCrusader.h"
#include "SealOfTheCrusaderBuff.h"

SealOfTheCrusader::SealOfTheCrusader(Paladin* pchar) :
    PaladinSeal("Seal of the Crusader", "Assets/spell/Spell_holy_holysmite.png", pchar,
                RestrictedByGcd::Yes,
                0,
                ResourceType::Mana, 160,
                new SealOfTheCrusaderBuff(pchar),
                new JudgementOfTheCrusader(pchar)),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Benediction", 5, DisabledAtZero::No)})
{}

void SealOfTheCrusader::increase_talent_rank_effect(const QString&, const int curr) {
    resource_cost = static_cast<int>(round(base_mana_cost * benediction_ranks[curr]));
}

void SealOfTheCrusader::decrease_talent_rank_effect(const QString&, const int curr) {
    resource_cost = static_cast<int>(round(base_mana_cost * benediction_ranks[curr]));
}
