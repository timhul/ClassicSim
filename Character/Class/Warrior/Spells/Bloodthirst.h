#ifndef BLOODTHIRST_H
#define BLOODTHIRST_H

#include "Spell.h"

class Warrior;

class Bloodthirst: public Spell {
public:
    Bloodthirst(Engine* engine, Character* pchar, CombatRoll* roll);

    void spell_effect() override;
protected:
private:
    Warrior* warr;

};

#endif // BLOODTHIRST_H
