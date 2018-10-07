
#include "MageSpells.h"
#include "Mage.h"

#include "MainhandAttack.h"


MageSpells::MageSpells(Mage* mage) :
    Spells(mage),
    mage(mage)
{
    this->mh_attack = new MainhandAttack(mage);

    spells.append(mh_attack);
}

MageSpells::~MageSpells() = default;

void MageSpells::reset() {
    for (auto & spell : spells) {
        spell->reset();
    }
}
