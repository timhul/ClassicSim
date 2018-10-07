#ifndef BLOODTHIRST_H
#define BLOODTHIRST_H

#include "Spell.h"

class Warrior;

class Bloodthirst: public Spell {
public:
    Bloodthirst(Engine* engine, Character* pchar, CombatRoll* roll);

protected:
private:
    Warrior* warr;

    void spell_effect() override;
};

#endif // BLOODTHIRST_H
