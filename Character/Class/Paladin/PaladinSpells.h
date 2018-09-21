#ifndef PALADINSPELLS_H
#define PALADINSPELLS_H

#include "Spells.h"

class Paladin;

class PaladinSpells: public Spells {
    Q_OBJECT

public:
    PaladinSpells(Paladin *paladin);
    virtual ~PaladinSpells() override;

    void reset() override;

private:
    Paladin* paladin;
};

#endif // PALADINSPELLS_H
