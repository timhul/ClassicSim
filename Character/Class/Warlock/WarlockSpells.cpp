
#include "WarlockSpells.h"
#include "Warlock.h"

#include "MainhandAttack.h"


WarlockSpells::WarlockSpells(Warlock* warlock) :
    Spells(warlock),
    warlock(warlock)
{
    this->mh_attack = new MainhandAttack(warlock);

    spells.append(mh_attack);
}

WarlockSpells::~WarlockSpells() = default;
