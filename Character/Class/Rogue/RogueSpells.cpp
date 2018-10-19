
#include "RogueSpells.h"
#include "Rogue.h"

#include "MainhandAttack.h"


RogueSpells::RogueSpells(Rogue* rogue) :
    Spells(rogue),
    rogue(rogue)
{
    this->mh_attack = new MainhandAttack(rogue);

    spells.append(mh_attack);
}

RogueSpells::~RogueSpells() = default;
