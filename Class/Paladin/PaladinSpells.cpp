#include "PaladinSpells.h"

#include "Buff.h"
#include "Consecration.h"
#include "Judgement.h"
#include "MainhandAttackPaladin.h"
#include "Paladin.h"
#include "PaladinSeal.h"
#include "SanctityAura.h"
#include "SealOfCommand.h"
#include "SealOfTheCrusader.h"

PaladinSpells::PaladinSpells(Paladin* paladin) :
    CharacterSpells(paladin),
    paladin(paladin)
{
    this->mh_attack = new MainhandAttackPaladin(paladin);

    add_spell_group({
                        new Consecration(paladin, new_cooldown_control("Consecration", 8.0), 1),
                        new Consecration(paladin, new_cooldown_control("Consecration", 8.0), 2),
                        new Consecration(paladin, new_cooldown_control("Consecration", 8.0), 3),
                        new Consecration(paladin, new_cooldown_control("Consecration", 8.0), 4),
                        new Consecration(paladin, new_cooldown_control("Consecration", 8.0), 5),
                    });
    add_spell_group({new Judgement(paladin, new_cooldown_control("Judgement", 10.0))});
    add_spell_group({mh_attack});
    add_spell_group({new SanctityAura(paladin)});
    add_spell_group({new SealOfCommand(paladin)});
    add_spell_group({new SealOfTheCrusader(paladin)});
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
