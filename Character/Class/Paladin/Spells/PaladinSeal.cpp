#include "PaladinSeal.h"

#include "Buff.h"
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
    seal->enable_buff();
}

PaladinSeal::~PaladinSeal() {
    delete seal;
    delete judge_debuff;
}

Buff* PaladinSeal::get_buff() const {
    return this->seal;
}

void PaladinSeal::judge_seal() {
    check((seal->is_active()), "Tried to judge an inactive seal");

    seal->cancel_buff();
    judge_debuff->apply_buff();
}

void PaladinSeal::spell_effect() {
    dynamic_cast<PaladinSpells*>(pchar->get_spells())->apply_seal(this);

    add_gcd_event();

    pchar->lose_mana(static_cast<unsigned>(resource_cost));
}
