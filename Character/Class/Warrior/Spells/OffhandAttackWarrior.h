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
    void spell_effect() override;
    void calculate_damage() override;
    Warrior* warr;
};

#endif // OFFHANDATTACKWARRIOR_H
