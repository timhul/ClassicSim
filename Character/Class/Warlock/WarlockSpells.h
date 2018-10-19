#ifndef WARLOCKSPELLS_H
#define WARLOCKSPELLS_H

#include "Spells.h"

class Warlock;

class WarlockSpells: public Spells {
    Q_OBJECT

public:
    WarlockSpells(Warlock *warlock);
    virtual ~WarlockSpells() override;

private:
    Warlock* warlock;
};

#endif // WARLOCKSPELLS_H
