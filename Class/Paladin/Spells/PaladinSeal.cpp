#include "PaladinSeal.h"

#include "Buff.h"
#include "CooldownControl.h"
#include "Paladin.h"
#include "PaladinSpells.h"
#include "Utils/Check.h"

PaladinSeal::PaladinSeal(QString name_,
                         QString icon_,
                         Paladin* paladin,
                         const RestrictedByGcd restricted_by_gcd_,
                         const ResourceType resource_type_,
                         unsigned resource_cost_,
                         Buff* seal) :
    Spell(name_, icon_, paladin, new CooldownControl(paladin, 0.0), restricted_by_gcd_, resource_type_, resource_cost_), seal(seal) {
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

    static_cast<PaladinSpells*>(pchar->get_spells())->judge_seal(this);
    seal->cancel_buff();

    judge_effect();
}

void PaladinSeal::spell_effect() {
    static_cast<PaladinSpells*>(pchar->get_spells())->apply_seal(this);

    cooldown->add_gcd_event();

    pchar->lose_mana(get_resource_cost());
}
