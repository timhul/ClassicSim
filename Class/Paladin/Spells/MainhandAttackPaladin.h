#ifndef MAINHANDATTACKPALADIN_H
#define MAINHANDATTACKPALADIN_H

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

    void spell_effect() override;
    int calculate_damage() override;
};

#endif // MAINHANDATTACKPALADIN_H
