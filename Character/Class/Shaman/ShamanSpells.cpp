
#include "ShamanSpells.h"
#include "Shaman.h"

#include "MainhandAttack.h"


ShamanSpells::ShamanSpells(Shaman* shaman) :
    Spells(shaman),
    shaman(shaman)
{
    this->mh_attack = new MainhandAttack(shaman->get_engine(), shaman, shaman->get_combat_roll());

    spells.append(mh_attack);
}

ShamanSpells::~ShamanSpells()
{}

void ShamanSpells::reset() {
    for (int i = 0; i < spells.size(); ++i) {
        spells[i]->reset();
    }
}
