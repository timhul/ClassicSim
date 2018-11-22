#ifndef ROGUESPELLS_H
#define ROGUESPELLS_H

#include "Spells.h"

class Backstab;
class Eviscerate;
class OffhandAttack;
class Rogue;
class SliceAndDice;

class RogueSpells: public Spells {
public:
    RogueSpells(Rogue *rogue);
    virtual ~RogueSpells() override;

    Backstab* get_backstab() const;
    Eviscerate* get_eviscerate() const;
    SliceAndDice* get_slice_and_dice() const;

private:
    Rogue* rogue;
    Backstab* backstab;
    Eviscerate* eviscerate;
    SliceAndDice* slice_and_dice;
};

#endif // ROGUESPELLS_H
