#ifndef PALADINSPELLS_H
#define PALADINSPELLS_H

#include "CharacterSpells.h"

class Paladin;

class PaladinSpells: public CharacterSpells {
public:
    PaladinSpells(Paladin *paladin);
    ~PaladinSpells() override;

private:
    Paladin* paladin;
};

#endif // PALADINSPELLS_H
