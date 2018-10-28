#ifndef PALADINSPELLS_H
#define PALADINSPELLS_H

#include "Spells.h"

class Paladin;

class PaladinSpells: public Spells {
public:
    PaladinSpells(Paladin *paladin);
    virtual ~PaladinSpells() override;

private:
    Paladin* paladin;
};

#endif // PALADINSPELLS_H
