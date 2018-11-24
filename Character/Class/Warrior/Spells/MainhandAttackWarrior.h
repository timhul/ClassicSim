#ifndef MAINHANDATTACKWARRIOR_H
#define MAINHANDATTACKWARRIOR_H

#include "Spell.h"
#include "MainhandAttack.h"

class Warrior;

class MainhandAttackWarrior: public MainhandAttack {
public:
    MainhandAttackWarrior(Character *pchar);

    void extra_attack() override;

protected:
private:
    Warrior* warr;

    void spell_effect() override;
    void calculate_damage(const bool) override;
};

#endif // MAINHANDATTACKWARRIOR_H
