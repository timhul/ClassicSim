#ifndef ROGUESPELLS_H
#define ROGUESPELLS_H

#include "Spells.h"

class Backstab;
class Eviscerate;
class OffhandAttack;
class Rogue;

class RogueSpells: public Spells {
public:
    RogueSpells(Rogue *rogue);
    virtual ~RogueSpells() override;

    Backstab* get_backstab() const;
    Eviscerate* get_eviscerate() const;

private:
    Rogue* rogue;
    Backstab* backstab;
    Eviscerate* eviscerate;
};

#endif // ROGUESPELLS_H
