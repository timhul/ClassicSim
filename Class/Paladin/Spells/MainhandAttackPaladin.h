#pragma once

#include "Spell.h"
#include "MainhandAttack.h"

class Paladin;

class MainhandAttackPaladin: public MainhandAttack {
public:
    MainhandAttackPaladin(Paladin* pchar);

    void apply_seal_of_the_crusader_penalty();
    void remove_seal_of_the_crusader_penalty();

private:
    Paladin* paladin;

    double sotc_penalty {1.0};

    void calculate_damage() override;
};
