
#include "PriestSpells.h"
#include "Priest.h"

#include "MainhandAttack.h"


PriestSpells::PriestSpells(Priest* pchar) :
    Spells(pchar),
    pchar(pchar)
{
    this->mh_attack = new MainhandAttack(pchar->get_engine(), pchar, pchar->get_combat_roll());

    spells.append(mh_attack);
}

PriestSpells::~PriestSpells()
{}

void PriestSpells::reset() {
    for (int i = 0; i < spells.size(); ++i) {
        spells[i]->reset();
    }
}
