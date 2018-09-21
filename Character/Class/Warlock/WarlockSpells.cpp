
#include "WarlockSpells.h"
#include "Warlock.h"

#include "MainhandAttack.h"


WarlockSpells::WarlockSpells(Warlock* warlock) :
    Spells(warlock),
    warlock(warlock)
{
    this->mh_attack = new MainhandAttack(warlock->get_engine(), warlock, warlock->get_combat_roll());

    spells.append(mh_attack);
}

WarlockSpells::~WarlockSpells()
{}

void WarlockSpells::reset() {
    for (int i = 0; i < spells.size(); ++i) {
        spells[i]->reset();
    }
}
