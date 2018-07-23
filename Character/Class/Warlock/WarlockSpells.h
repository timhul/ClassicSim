#ifndef WARLOCKSPELLS_H
#define WARLOCKSPELLS_H

#include "Spells.h"

class Warlock;

class WarlockSpells: public Spells {
    Q_OBJECT

public:
    WarlockSpells(Warlock *pchar);
    virtual ~WarlockSpells() override;

    void reset() override;

private:
    Warlock* pchar;
};

#endif // WARLOCKSPELLS_H
