#ifndef ROGUESPELLS_H
#define ROGUESPELLS_H

#include "Spells.h"

class AdrenalineRush;
class Backstab;
class BladeFlurry;
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

    AdrenalineRush* get_adrenaline_rush() const;
    Backstab* get_backstab() const;
    BladeFlurry* get_blade_flurry() const;
    Eviscerate* get_eviscerate() const;
    SliceAndDice* get_slice_and_dice() const;

private:
    Rogue* rogue;
    AdrenalineRush* adrenaline_rush;
    Backstab* backstab;
    BladeFlurry* blade_flurry;
    Eviscerate* eviscerate;
    SliceAndDice* slice_and_dice;
};

#endif // ROGUESPELLS_H
