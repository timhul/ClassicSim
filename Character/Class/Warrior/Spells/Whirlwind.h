#ifndef WHIRLWIND_H
#define WHIRLWIND_H

#include "Spell.h"
#include "CooldownReady.h"

class Whirlwind: public Spell {
public:
    Whirlwind(Engine* engine, Character* pchar, CombatRoll* roll) :
        Spell("Whirlwind", engine, pchar, roll, 10.0, 25) {}

    int spell_effect(const int) const override;
protected:
private:
};



#endif // WHIRLWIND_H
