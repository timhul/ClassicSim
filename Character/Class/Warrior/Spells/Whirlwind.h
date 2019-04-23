#ifndef WHIRLWIND_H
#define WHIRLWIND_H

#include "Spell.h"

class Warrior;

class Whirlwind: public Spell {
public:
    Whirlwind(Character* pchar);

private:
    Warrior* warr;

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;
};

#endif // WHIRLWIND_H
