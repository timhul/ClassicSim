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

    void oh_auto_attack(const int) override;
    void add_next_oh_attack(void) override;
    OffhandAttack* get_oh_attack() const override;

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
