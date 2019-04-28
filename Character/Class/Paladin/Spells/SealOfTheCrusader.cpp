#include "SealOfTheCrusader.h"

#include "CombatRoll.h"
#include "CharacterStats.h"
#include "JudgementOfTheCrusader.h"
#include "Paladin.h"
#include "SealOfTheCrusaderBuff.h"

SealOfTheCrusader::SealOfTheCrusader(Paladin* pchar) :
    PaladinSeal("Seal of the Crusader", "Assets/spell/Spell_holy_holysmite.png", pchar,
                RestrictedByGcd::Yes,
                0,
                ResourceType::Mana, 160,
                new SealOfTheCrusaderBuff(pchar)),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Benediction", 5, DisabledAtZero::No)}),
    judge_debuff(new JudgementOfTheCrusader(pchar))
{
    judge_debuff->enable_buff();
}

SealOfTheCrusader::~SealOfTheCrusader() {
    delete judge_debuff;
}

void SealOfTheCrusader::refresh_seal() const {
    if (judge_debuff->is_active())
        judge_debuff->apply_buff();
}

Buff* SealOfTheCrusader::get_judge_debuff() const {
    return this->judge_debuff;
}

void SealOfTheCrusader::judge_effect() {
    const int result = roll->get_ranged_hit_result(pchar->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        return;
    }

    judge_debuff->apply_buff();
}

void SealOfTheCrusader::increase_talent_rank_effect(const QString&, const int curr) {
    resource_cost = static_cast<int>(round(base_mana_cost * benediction_ranks[curr]));
}

void SealOfTheCrusader::decrease_talent_rank_effect(const QString&, const int curr) {
    resource_cost = static_cast<int>(round(base_mana_cost * benediction_ranks[curr]));
}
