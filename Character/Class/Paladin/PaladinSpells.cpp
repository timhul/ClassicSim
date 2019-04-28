#include "PaladinSpells.h"

#include "Buff.h"
#include "Consecration.h"
#include "Judgement.h"
#include "MainhandAttackPaladin.h"
#include "ManaPotion.h"
#include "Paladin.h"
#include "PaladinSeal.h"
#include "SanctityAura.h"
#include "SealOfCommand.h"
#include "SealOfTheCrusader.h"

PaladinSpells::PaladinSpells(Paladin* paladin) :
    CharacterSpells(paladin),
    paladin(paladin)
{
    this->consecration = new Consecration(paladin);
    this->judgement = new Judgement(paladin);
    this->mana_potion = new ManaPotion(paladin);
    this->mh_attack = new MainhandAttackPaladin(paladin);
    this->sanctity_aura = new SanctityAura(paladin);
    this->seal_of_command = new SealOfCommand(paladin);
    this->seal_of_the_crusader = new SealOfTheCrusader(paladin);

    spells.append(consecration);
    spells.append(judgement);
    spells.append(mana_potion);
    spells.append(mh_attack);
    spells.append(sanctity_aura);
    spells.append(seal_of_command);
    spells.append(seal_of_the_crusader);
}

Judgement* PaladinSpells::get_judgement() const {
    return this->judgement;
}

ManaPotion* PaladinSpells::get_mana_potion() const {
    return this->mana_potion;
}

PaladinSeal* PaladinSpells::get_seal_of_the_crusader() const {
    return this->seal_of_the_crusader;
}

PaladinSeal* PaladinSpells::get_seal_of_command() const {
    return this->seal_of_command;
}

Consecration* PaladinSpells::get_consecration() const {
    return this->consecration;
}

SanctityAura* PaladinSpells::get_sanctity_aura() const {
    return this->sanctity_aura;
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
