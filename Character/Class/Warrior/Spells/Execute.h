#ifndef EXECUTE_H
#define EXECUTE_H

#include "Spell.h"

class Warrior;

class Execute: public Spell {
public:
    Execute(Engine* engine, Character* pchar, CombatRoll* roll);

    int spell_effect(const int) const override;
protected:
private:
    Warrior* pchar;
};

#endif // EXECUTE_H
