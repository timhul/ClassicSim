#ifndef MAINHANDATTACK_H
#define MAINHANDATTACK_H

#include "Spell.h"

class Warrior;

class MainhandAttack: public Spell {
public:
    MainhandAttack(Engine* engine, Character *pchar, CombatRoll* roll);

protected:
private:
    int spell_effect(const int) const override;
    Warrior* pchar;
};

#endif // MAINHANDATTACK_H
