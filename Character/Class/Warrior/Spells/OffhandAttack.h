#ifndef OFFHANDATTACK_H
#define OFFHANDATTACK_H

#include "Spell.h"

class Warrior;

class OffhandAttack: public Spell {
public:
    OffhandAttack(Engine* engine, Character* pchar, CombatRoll* roll);

protected:
private:
    int spell_effect(const int) const override;
    Warrior* pchar;
};

#endif // OFFHANDATTACK_H
