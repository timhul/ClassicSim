#include "HunterSpells.h"

#include "Hunter.h"
#include "MainhandAttack.h"

HunterSpells::HunterSpells(Hunter* hunter) :
    CharacterSpells(hunter),
    hunter(hunter)
{
    this->mh_attack = new MainhandAttack(hunter);

    spells.append(mh_attack);
}

HunterSpells::~HunterSpells() = default;
