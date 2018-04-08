#ifndef BLOODTHIRST_H
#define BLOODTHIRST_H

#include "Spell.h"

class Warrior;

class Bloodthirst: public Spell {
public:
    Bloodthirst(Engine* engine, Character* pchar, CombatRoll* roll);

    int spell_effect(const int) override;
protected:
private:
    Warrior* pchar;

};

#endif // BLOODTHIRST_H
