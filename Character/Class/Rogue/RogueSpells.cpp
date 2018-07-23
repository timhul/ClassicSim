
#include "RogueSpells.h"
#include "Rogue.h"

#include "MainhandAttack.h"


RogueSpells::RogueSpells(Rogue* pchar) :
    Spells(pchar),
    pchar(pchar)
{
    this->mh_attack = new MainhandAttack(pchar->get_engine(), pchar, pchar->get_combat_roll());

    spells.append(mh_attack);
}

RogueSpells::~RogueSpells()
{}

void RogueSpells::reset() {
    for (int i = 0; i < spells.size(); ++i) {
        spells[i]->reset();
    }
}
