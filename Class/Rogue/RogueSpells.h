#pragma once

#include "CharacterSpells.h"

class OffhandAttack;
class Rogue;

class RogueSpells: public CharacterSpells {
public:
    RogueSpells(Rogue *rogue);

    void oh_auto_attack(const int) override;
    void add_next_oh_attack() override;
    OffhandAttack* get_oh_attack() const override;

private:
    Rogue* rogue;
};
