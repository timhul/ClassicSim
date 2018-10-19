#ifndef PRIESTSPELLS_H
#define PRIESTSPELLS_H

#include "Spells.h"

class Priest;

class PriestSpells: public Spells {
    Q_OBJECT

public:
    PriestSpells(Priest *priest);
    virtual ~PriestSpells() override;

private:
    Priest* priest;
};

#endif // PRIESTSPELLS_H
