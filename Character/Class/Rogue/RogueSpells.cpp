#include "Backstab.h"
#include "Eviscerate.h"
#include "MainhandAttack.h"
#include "OffhandAttack.h"
#include "Rogue.h"
#include "RogueSpells.h"
#include "SliceAndDice.h"

RogueSpells::RogueSpells(Rogue* rogue) :
    Spells(rogue),
    rogue(rogue)
{
    this->mh_attack = new MainhandAttack(rogue);
    this->oh_attack = new OffhandAttack(rogue);
    this->backstab = new Backstab(rogue);
    this->eviscerate = new Eviscerate(rogue);
    this->slice_and_dice = new SliceAndDice(rogue);

    spells.append(mh_attack);
    spells.append(oh_attack);
    spells.append(backstab);
    spells.append(eviscerate);
    spells.append(slice_and_dice);
}

RogueSpells::~RogueSpells() = default;

Backstab* RogueSpells::get_backstab() const {
    return this->backstab;
}

Eviscerate* RogueSpells::get_eviscerate() const {
    return this->eviscerate;
}

SliceAndDice* RogueSpells::get_slice_and_dice() const {
    return this->slice_and_dice;
}
