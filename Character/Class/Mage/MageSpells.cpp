
#include "MageSpells.h"
#include "Mage.h"

#include "MainhandAttack.h"


MageSpells::MageSpells(Mage* mage) :
    Spells(mage),
    mage(mage)
{
    this->mh_attack = new MainhandAttack(mage->get_engine(), mage, mage->get_combat_roll());

    spells.append(mh_attack);
}

MageSpells::~MageSpells()
{}

void MageSpells::reset() {
    for (int i = 0; i < spells.size(); ++i) {
        spells[i]->reset();
    }
}
