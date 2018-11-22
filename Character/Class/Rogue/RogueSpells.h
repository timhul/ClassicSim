#ifndef ROGUESPELLS_H
#define ROGUESPELLS_H

#include "Spells.h"

class Backstab;
class OffhandAttack;
class Rogue;

class RogueSpells: public Spells {
public:
    RogueSpells(Rogue *rogue);
    virtual ~RogueSpells() override;

    Backstab* get_backstab() const;

private:
    Rogue* rogue;
    Backstab* backstab;
};

#endif // ROGUESPELLS_H
