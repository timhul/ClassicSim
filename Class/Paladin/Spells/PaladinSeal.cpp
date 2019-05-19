#include "PaladinSeal.h"

#include "Buff.h"
#include "CooldownControl.h"
#include "Paladin.h"
#include "PaladinSpells.h"
#include "Utils/Check.h"

PaladinSeal::PaladinSeal(QString name,
                         QString icon,
                         Paladin* pchar,
                         bool restricted_by_gcd,
                         const ResourceType resource_type,
                         unsigned resource_cost,
                         Buff* seal) :
    Spell(name, icon, pchar, new CooldownControl(pchar, 0.0), restricted_by_gcd, resource_type, resource_cost),
    seal(seal)
{
    seal->enable_buff();
}

PaladinSeal::~PaladinSeal() {
    delete seal;
    delete cooldown;
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

    cooldown->add_gcd_event();

    pchar->lose_mana(resource_cost);
}
