#ifndef WHIRLWIND_H
#define WHIRLWIND_H

#include "Spell.h"

class Warrior;

class Whirlwind: public Spell {
public:
    Whirlwind(Engine* engine, Character* pchar, CombatRoll* roll);

    void spell_effect() override;
    bool is_ready_spell_specific() const override;

protected:
private:
    Warrior* pchar;
};



#endif // WHIRLWIND_H
