#ifndef MAINHANDATTACKWARRIOR_H
#define MAINHANDATTACKWARRIOR_H

#include "Spell.h"
#include "MainhandAttack.h"

class Warrior;

class MainhandAttackWarrior: public MainhandAttack {
public:
    MainhandAttackWarrior(Engine* engine, Character *pchar, CombatRoll* roll);

    void extra_attack() override;

protected:
private:
    void spell_effect() override;
    void calculate_damage() override;
    Warrior* warr;
};

#endif // MAINHANDATTACKWARRIOR_H
