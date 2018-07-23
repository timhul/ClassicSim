#ifndef ROGUESPELLS_H
#define ROGUESPELLS_H

#include "Spells.h"

class Rogue;

class RogueSpells: public Spells {
    Q_OBJECT

public:
    RogueSpells(Rogue *pchar);
    virtual ~RogueSpells() override;

    void reset() override;

private:
    Rogue* pchar;
};

#endif // ROGUESPELLS_H
