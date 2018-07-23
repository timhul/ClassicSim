#ifndef PRIESTSPELLS_H
#define PRIESTSPELLS_H

#include "Spells.h"

class Priest;

class PriestSpells: public Spells {
    Q_OBJECT

public:
    PriestSpells(Priest *pchar);
    virtual ~PriestSpells() override;

    void reset() override;

private:
    Priest* pchar;
};

#endif // PRIESTSPELLS_H
