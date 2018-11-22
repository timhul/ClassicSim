#include "Backstab.h"
#include "Eviscerate.h"
#include "MainhandAttack.h"
#include "OffhandAttack.h"
#include "Rogue.h"
#include "RogueSpells.h"

RogueSpells::RogueSpells(Rogue* rogue) :
    Spells(rogue),
    rogue(rogue)
{
    this->mh_attack = new MainhandAttack(rogue);
    this->oh_attack = new OffhandAttack(rogue);
    this->backstab = new Backstab(rogue);
    this->eviscerate = new Eviscerate(rogue);

    spells.append(mh_attack);
    spells.append(oh_attack);
    spells.append(backstab);
    spells.append(eviscerate);
}

RogueSpells::~RogueSpells() = default;

Backstab* RogueSpells::get_backstab() const {
    return this->backstab;
}

Eviscerate* RogueSpells::get_eviscerate() const {
    return this->eviscerate;
}
