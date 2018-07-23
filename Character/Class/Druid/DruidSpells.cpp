
#include "DruidSpells.h"
#include "Druid.h"

#include "MainhandAttack.h"


DruidSpells::DruidSpells(Druid* pchar) :
    Spells(pchar),
    pchar(pchar)
{
    this->mh_attack = new MainhandAttack(pchar->get_engine(), pchar, pchar->get_combat_roll());

    spells.append(mh_attack);
}

DruidSpells::~DruidSpells()
{}

void DruidSpells::reset() {
    for (int i = 0; i < spells.size(); ++i) {
        spells[i]->reset();
    }
}
