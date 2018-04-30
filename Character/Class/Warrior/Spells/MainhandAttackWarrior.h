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
    int spell_effect(const int) override;
    int calculate_damage() override;
    Warrior* pchar;
};

#endif // MAINHANDATTACKWARRIOR_H
