#include "PaladinSpells.h"

#include "Buff.h"
#include "MainhandAttackPaladin.h"
#include "ManaPotion.h"
#include "Paladin.h"
#include "PaladinSeal.h"
#include "SealOfTheCrusader.h"

PaladinSpells::PaladinSpells(Paladin* paladin) :
    CharacterSpells(paladin),
    paladin(paladin)
{
    this->mana_potion = new ManaPotion(paladin);
    this->mh_attack = new MainhandAttackPaladin(paladin);
    this->seal_of_the_crusader = new SealOfTheCrusader(paladin);

    spells.append(mana_potion);
    spells.append(mh_attack);
    spells.append(seal_of_the_crusader);
}

ManaPotion* PaladinSpells::get_mana_potion() const {
    return this->mana_potion;
}

PaladinSeal* PaladinSpells::get_seal_of_the_crusader() const {
    return this->seal_of_the_crusader;
}

void PaladinSpells::apply_seal(PaladinSeal* new_seal) {
    if (current_seal != nullptr && current_seal->get_buff()->get_instance_id() != new_seal->get_buff()->get_instance_id())
        current_seal->get_buff()->cancel_buff();

    current_seal = new_seal;
    current_seal->get_buff()->apply_buff();
}

PaladinSeal* PaladinSpells::get_seal() const {
    return this->current_seal;
}
