
#include "PaladinSpells.h"
#include "Paladin.h"

#include "MainhandAttack.h"


PaladinSpells::PaladinSpells(Paladin* paladin) :
    Spells(paladin),
    paladin(paladin)
{
    this->mh_attack = new MainhandAttack(paladin->get_engine(), paladin, paladin->get_combat_roll());

    spells.append(mh_attack);
}

PaladinSpells::~PaladinSpells()
{}

void PaladinSpells::reset() {
    for (int i = 0; i < spells.size(); ++i) {
        spells[i]->reset();
    }
}
