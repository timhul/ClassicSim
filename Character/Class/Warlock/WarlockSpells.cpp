
#include "WarlockSpells.h"
#include "Warlock.h"

#include "MainhandAttack.h"


WarlockSpells::WarlockSpells(Warlock* pchar) :
    Spells(pchar),
    pchar(pchar)
{
    this->mh_attack = new MainhandAttack(pchar->get_engine(), pchar, pchar->get_combat_roll());

    spells.append(mh_attack);
}

WarlockSpells::~WarlockSpells()
{}

void WarlockSpells::reset() {
    for (int i = 0; i < spells.size(); ++i) {
        spells[i]->reset();
    }
}
