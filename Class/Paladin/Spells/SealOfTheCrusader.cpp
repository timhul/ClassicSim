#include "SealOfTheCrusader.h"

#include "CharacterStats.h"
#include "CombatRoll.h"
#include "JudgementOfTheCrusader.h"
#include "Paladin.h"
#include "SealOfTheCrusaderBuff.h"
#include "Utils/Check.h"

SealOfTheCrusader::SealOfTheCrusader(Paladin* pchar, JudgementOfTheCrusader* judge_debuff) :
    PaladinSeal("Seal of the Crusader",
                "Assets/spell/Spell_holy_holysmite.png",
                pchar,
                RestrictedByGcd::Yes,
                ResourceType::Mana,
                160,
                new SealOfTheCrusaderBuff(pchar),
                judge_debuff),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo("Benediction", 5, DisabledAtZero::No)}),
    ItemModificationRequirer({22401, 23203}) {}

SealOfTheCrusader::~SealOfTheCrusader() {}

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
    resource_cost = static_cast<unsigned>(round(base_mana_cost * benediction_ranks[curr]));
}

void SealOfTheCrusader::decrease_talent_rank_effect(const QString&, const int curr) {
    resource_cost = static_cast<unsigned>(round(base_mana_cost * benediction_ranks[curr]));
}

void SealOfTheCrusader::activate_item_effect(const int item_id) {
    switch (item_id) {
    case 22401:
        resource_cost -= 20;
        break;
    case 23203:
        break;
    default:
        check(false, "SealOfTheCrusader::activate_item_effect reached end of switch");
    }
}

void SealOfTheCrusader::deactivate_item_effect(const int item_id) {
    switch (item_id) {
    case 22401:
        resource_cost += 20;
        break;
    case 23203:
        break;
    default:
        check(false, "SealOfTheCrusader::deactivate_item_effect reached end of switch");
    }
}
