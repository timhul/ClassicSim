#ifndef OFFHANDATTACKWARRIOR_H
#define OFFHANDATTACKWARRIOR_H

#include "Spell.h"
#include "OffhandAttack.h"

class Warrior;

class OffhandAttackWarrior: public OffhandAttack {
public:
    OffhandAttackWarrior(Engine* engine, Character* pchar, CombatRoll* roll);

    void extra_attack() override;

protected:
private:
    Warrior* warr;

    void spell_effect() override;
    void calculate_damage() override;
};

#endif // OFFHANDATTACKWARRIOR_H
