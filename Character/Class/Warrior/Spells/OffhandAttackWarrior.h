#ifndef OFFHANDATTACKWARRIOR_H
#define OFFHANDATTACKWARRIOR_H

#include "Spell.h"
#include "OffhandAttack.h"

class Warrior;

class OffhandAttackWarrior: public OffhandAttack {
public:
    OffhandAttackWarrior(Engine* engine, Character* pchar, CombatRoll* roll);

protected:
private:
    int spell_effect(const int) override;
    Warrior* pchar;
};

#endif // OFFHANDATTACKWARRIOR_H
