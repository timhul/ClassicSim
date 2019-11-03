#pragma once

#include "Spell.h"
#include "MainhandAttack.h"

class Paladin;
class PaladinSpells;

class MainhandAttackPaladin: public MainhandAttack {
public:
    MainhandAttackPaladin(Paladin* pchar, PaladinSpells* paladin_spells);

    void apply_seal_of_the_crusader_penalty();
    void remove_seal_of_the_crusader_penalty();

private:
    Paladin* paladin;
    PaladinSpells* paladin_spells;

    double sotc_penalty {1.0};

    void calculate_damage() override;
};
