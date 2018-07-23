
#include "MageSpells.h"
#include "Mage.h"

#include "MainhandAttack.h"


MageSpells::MageSpells(Mage* pchar) :
    Spells(pchar),
    pchar(pchar)
{
    this->mh_attack = new MainhandAttack(pchar->get_engine(), pchar, pchar->get_combat_roll());

    spells.append(mh_attack);
}

MageSpells::~MageSpells()
{}

void MageSpells::reset() {
    for (int i = 0; i < spells.size(); ++i) {
        spells[i]->reset();
    }
}
