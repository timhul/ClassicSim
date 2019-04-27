#include "PaladinSeal.h"

#include "Buff.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "Paladin.h"
#include "PaladinSpells.h"
#include "Utils/Check.h"

PaladinSeal::PaladinSeal(QString name,
                         QString icon,
                         Paladin* pchar,
                         bool restricted_by_gcd,
                         double cooldown,
                         const ResourceType resource_type,
                         int resource_cost,
                         Buff* seal,
                         Buff* judge_debuff) :
    Spell(name, icon, pchar, restricted_by_gcd, cooldown, resource_type, resource_cost),
    seal(seal),
    judge_debuff(judge_debuff)
{
    judge_debuff->enable_buff();
    seal->enable_buff();
}

PaladinSeal::~PaladinSeal() {
    delete seal;
    delete judge_debuff;
}

Buff* PaladinSeal::get_buff() const {
    return this->seal;
}

Buff* PaladinSeal::get_judge_debuff() const {
    return this->judge_debuff;
}

void PaladinSeal::judge_seal() {
    check((seal->is_active()), "Tried to judge an inactive seal");

    seal->cancel_buff();

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

void PaladinSeal::spell_effect() {
    dynamic_cast<PaladinSpells*>(pchar->get_spells())->apply_seal(this);

    add_gcd_event();

    pchar->lose_mana(static_cast<unsigned>(resource_cost));
}
