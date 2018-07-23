
#include "ShamanSpells.h"
#include "Shaman.h"

#include "MainhandAttack.h"


ShamanSpells::ShamanSpells(Shaman* pchar) :
    Spells(pchar),
    pchar(pchar)
{
    this->mh_attack = new MainhandAttack(pchar->get_engine(), pchar, pchar->get_combat_roll());

    spells.append(mh_attack);
}

ShamanSpells::~ShamanSpells()
{}

void ShamanSpells::reset() {
    for (int i = 0; i < spells.size(); ++i) {
        spells[i]->reset();
    }
}
