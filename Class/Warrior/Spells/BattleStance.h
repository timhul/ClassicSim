#pragma once

#include "Spell.h"

class Warrior;

class BattleStance: public Spell {
public:
    BattleStance(Warrior* warrior);
    ~BattleStance() override;

private:
    Warrior* warrior;

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;
};
