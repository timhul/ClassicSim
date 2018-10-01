
#include "DruidSpells.h"
#include "Druid.h"

#include "MainhandAttack.h"


DruidSpells::DruidSpells(Druid* druid) :
    Spells(druid),
    druid(druid)
{
    this->mh_attack = new MainhandAttack(druid->get_engine(), druid, druid->get_combat_roll());

    spells.append(mh_attack);
}

DruidSpells::~DruidSpells() = default;

void DruidSpells::reset() {
    for (auto & spell : spells) {
        spell->reset();
    }
}
