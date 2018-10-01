
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

HunterSpells::~HunterSpells() = default;

void HunterSpells::reset() {
    for (auto & spell : spells) {
        spell->reset();
    }
}
