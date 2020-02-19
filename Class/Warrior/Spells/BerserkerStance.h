#pragma once

#include "Spell.h"

class Warrior;

class BerserkerStance : public Spell {
public:
    BerserkerStance(Warrior* warrior);
    ~BerserkerStance() override;

private:
    Warrior* warrior;

    SpellStatus is_ready_spell_specific() const override;
    void spell_effect() override;
};
