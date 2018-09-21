
#include "RogueSpells.h"
#include "Rogue.h"

#include "MainhandAttack.h"


RogueSpells::RogueSpells(Rogue* rogue) :
    Spells(rogue),
    rogue(rogue)
{
    this->mh_attack = new MainhandAttack(rogue->get_engine(), rogue, rogue->get_combat_roll());

    spells.append(mh_attack);
}

RogueSpells::~RogueSpells()
{}

void RogueSpells::reset() {
    for (int i = 0; i < spells.size(); ++i) {
        spells[i]->reset();
    }
}
