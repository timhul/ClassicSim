
#include "HunterSpells.h"
#include "Hunter.h"

#include "MainhandAttack.h"


HunterSpells::HunterSpells(Hunter* hunter) :
    Spells(hunter),
    hunter(hunter)
{
    this->mh_attack = new MainhandAttack(hunter->get_engine(), hunter, hunter->get_combat_roll());

    spells.append(mh_attack);
}

HunterSpells::~HunterSpells()
{}

void HunterSpells::reset() {
    for (int i = 0; i < spells.size(); ++i) {
        spells[i]->reset();
    }
}
