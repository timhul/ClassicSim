
#include "PriestSpells.h"
#include "Priest.h"

#include "MainhandAttack.h"


PriestSpells::PriestSpells(Priest* priest) :
    Spells(priest),
    priest(priest)
{
    this->mh_attack = new MainhandAttack(priest);

    spells.append(mh_attack);
}

PriestSpells::~PriestSpells() = default;
