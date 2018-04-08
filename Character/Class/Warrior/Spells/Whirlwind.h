#ifndef WHIRLWIND_H
#define WHIRLWIND_H

#include "Spell.h"

class Warrior;

class Whirlwind: public Spell {
public:
    Whirlwind(Engine* engine, Character* pchar, CombatRoll* roll);

    int spell_effect(const int) override;
protected:
private:
    Warrior* pchar;
};



#endif // WHIRLWIND_H
