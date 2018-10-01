
#include "PriestSpells.h"
#include "Priest.h"

#include "MainhandAttack.h"


PriestSpells::PriestSpells(Priest* priest) :
    Spells(priest),
    priest(priest)
{
    this->mh_attack = new MainhandAttack(priest->get_engine(), priest, priest->get_combat_roll());

    spells.append(mh_attack);
}

PriestSpells::~PriestSpells() = default;

void PriestSpells::reset() {
    for (auto & spell : spells) {
        spell->reset();
    }
}
