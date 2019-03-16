#ifndef WARLOCKSPELLS_H
#define WARLOCKSPELLS_H

#include "CharacterSpells.h"

class Warlock;

class WarlockSpells: public CharacterSpells {
public:
    WarlockSpells(Warlock *warlock);
    virtual ~WarlockSpells() override;

private:
    Warlock* warlock;
};

#endif // WARLOCKSPELLS_H
