
#include "PaladinSpells.h"
#include "Paladin.h"

#include "MainhandAttack.h"


PaladinSpells::PaladinSpells(Paladin* pchar) :
    Spells(pchar),
    pchar(pchar)
{
    this->mh_attack = new MainhandAttack(pchar->get_engine(), pchar, pchar->get_combat_roll());

    spells.append(mh_attack);
}

PaladinSpells::~PaladinSpells()
{}

void PaladinSpells::reset() {
    for (int i = 0; i < spells.size(); ++i) {
        spells[i]->reset();
    }
}
