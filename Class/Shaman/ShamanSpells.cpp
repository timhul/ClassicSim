#include "ShamanSpells.h"

#include "MainhandAttack.h"
#include "Shaman.h"
#include "Stormstrike.h"


ShamanSpells::ShamanSpells(Shaman* shaman) :
    CharacterSpells(shaman),
    shaman(shaman)
{
    this->mh_attack = new MainhandAttack(shaman);

    add_spell_group({mh_attack});
    add_spell_group({new Stormstrike(shaman, this)});
}
