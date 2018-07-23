
#include "HunterSpells.h"
#include "Hunter.h"

#include "MainhandAttack.h"


HunterSpells::HunterSpells(Hunter* pchar) :
    Spells(pchar),
    pchar(pchar)
{
    this->mh_attack = new MainhandAttack(pchar->get_engine(), pchar, pchar->get_combat_roll());

    spells.append(mh_attack);
}

HunterSpells::~HunterSpells()
{}

void HunterSpells::reset() {
    for (int i = 0; i < spells.size(); ++i) {
        spells[i]->reset();
    }
}
