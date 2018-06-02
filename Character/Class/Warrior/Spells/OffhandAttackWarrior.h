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
    int spell_effect(const int) override;
    int calculate_damage() override;
    Warrior* pchar;
};

#endif // OFFHANDATTACKWARRIOR_H
