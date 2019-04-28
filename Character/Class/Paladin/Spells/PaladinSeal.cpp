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
                         Buff* seal) :
    Spell(name, icon, pchar, restricted_by_gcd, cooldown, resource_type, resource_cost),
    seal(seal)
{
    seal->enable_buff();
}

PaladinSeal::~PaladinSeal() {
    delete seal;
}

Buff* PaladinSeal::get_buff() const {
    return this->seal;
}

void PaladinSeal::judge_seal() {
    check((seal->is_active()), "Tried to judge an inactive seal");

    seal->cancel_buff();

    judge_effect();
}

void PaladinSeal::spell_effect() {
    dynamic_cast<PaladinSpells*>(pchar->get_spells())->apply_seal(this);

    add_gcd_event();

    pchar->lose_mana(static_cast<unsigned>(resource_cost));
}
