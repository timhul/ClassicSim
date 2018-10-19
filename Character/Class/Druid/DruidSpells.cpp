
#include "DruidSpells.h"
#include "Druid.h"

#include "MainhandAttack.h"


DruidSpells::DruidSpells(Druid* druid) :
    Spells(druid),
    druid(druid)
{
    this->mh_attack = new MainhandAttack(druid);

    spells.append(mh_attack);
}

DruidSpells::~DruidSpells() = default;
