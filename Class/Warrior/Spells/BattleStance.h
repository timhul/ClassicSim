#pragma once

#include "Spell.h"

class Warrior;

class BattleStance: public Spell {
public:
    BattleStance(Character* pchar);
    ~BattleStance() override;

private:
    Warrior* warr;

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;
};
