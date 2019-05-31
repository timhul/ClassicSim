#include "ShamanSpells.h"

#include "LightningBolt.h"
#include "MainhandAttack.h"
#include "Shaman.h"
#include "Stormstrike.h"
#include "WindfuryWeapon.h"

ShamanSpells::ShamanSpells(Shaman* shaman) :
    CharacterSpells(shaman),
    shaman(shaman)
{
    this->mh_attack = new MainhandAttack(shaman);

    add_spell_group({mh_attack});
    add_spell_group({new Stormstrike(shaman, this)});

    add_spell_group({
                        new LightningBolt(shaman, 1),
                        new LightningBolt(shaman, 2),
                        new LightningBolt(shaman, 3),
                        new LightningBolt(shaman, 4),
                        new LightningBolt(shaman, 5),
                        new LightningBolt(shaman, 6),
                        new LightningBolt(shaman, 7),
                        new LightningBolt(shaman, 8),
                        new LightningBolt(shaman, 9),
                        new LightningBolt(shaman, 10),
                    });

    add_spell_group({
                        new WindfuryWeapon(shaman, 1),
                        new WindfuryWeapon(shaman, 2),
                        new WindfuryWeapon(shaman, 3),
                        new WindfuryWeapon(shaman, 4),
                    });
}
