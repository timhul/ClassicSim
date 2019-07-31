#include "DruidSpells.h"

#include "Druid.h"
#include "MainhandAttack.h"
#include "Moonfire.h"
#include "Wrath.h"

DruidSpells::DruidSpells(Druid* druid) :
    CharacterSpells(druid),
    druid(druid)
{
    this->mh_attack = new MainhandAttack(druid);
    add_spell_group({mh_attack});

    add_spell_group({
                        new Wrath(druid, this, 4),
                        new Wrath(druid, this, 5),
                        new Wrath(druid, this, 6),
                        new Wrath(druid, this, 7),
                        new Wrath(druid, this, 8),
                    });

    add_spell_group({
                        new Moonfire(druid, this, 1),
                        new Moonfire(druid, this, 2),
                        new Moonfire(druid, this, 3),
                        new Moonfire(druid, this, 4),
                        new Moonfire(druid, this, 5),
                        new Moonfire(druid, this, 6),
                        new Moonfire(druid, this, 7),
                        new Moonfire(druid, this, 8),
                        new Moonfire(druid, this, 9),
                        new Moonfire(druid, this, 10),
                    });
}

DruidSpells::~DruidSpells() = default;
