#pragma once

#include "Spell.h"

class Warrior;

class DefensiveStance : public Spell {
public:
    DefensiveStance(Warrior* warrior);
    ~DefensiveStance() override;

private:
    Warrior* warrior;

    SpellStatus is_ready_spell_specific() const override;
    void spell_effect() override;
};
