#ifndef PALADINSPELLS_H
#define PALADINSPELLS_H

#include "Spells.h"

class Paladin;

class PaladinSpells: public Spells {
    Q_OBJECT

public:
    PaladinSpells(Paladin *pchar);
    virtual ~PaladinSpells() override;

    void reset() override;

private:
    Paladin* pchar;
};

#endif // PALADINSPELLS_H
