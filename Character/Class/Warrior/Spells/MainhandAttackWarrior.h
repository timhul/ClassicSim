#ifndef MAINHANDATTACKWARRIOR_H
#define MAINHANDATTACKWARRIOR_H

#include "Spell.h"
#include "MainhandAttack.h"

class Warrior;

class MainhandAttackWarrior: public MainhandAttack {
public:
    MainhandAttackWarrior(Engine* engine, Character *pchar, CombatRoll* roll);

protected:
private:
    int spell_effect(const int) override;
    Warrior* pchar;
};

#endif // MAINHANDATTACKWARRIOR_H
