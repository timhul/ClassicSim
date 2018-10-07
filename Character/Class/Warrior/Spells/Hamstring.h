#ifndef HAMSTRING_H
#define HAMSTRING_H

#include "Spell.h"

class Warrior;

class Hamstring: public Spell {
public:
    Hamstring(Engine* engine, Character* pchar, CombatRoll* roll);

protected:
private:
    Warrior* warr;

    void spell_effect() override;
};

#endif // HAMSTRING_H
