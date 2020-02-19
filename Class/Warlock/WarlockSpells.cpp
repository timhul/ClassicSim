#include "WarlockSpells.h"

#include "MainhandAttack.h"
#include "Warlock.h"

WarlockSpells::WarlockSpells(Warlock* warlock) : CharacterSpells(warlock), warlock(warlock) {
    this->mh_attack = new MainhandAttack(warlock);

    spells.append(mh_attack);
}
