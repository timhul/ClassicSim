#ifndef WHIRLWIND_H
#define WHIRLWIND_H

#include "Spell.h"

class Warrior;
class WarriorSpells;

class Whirlwind: public Spell {
public:
    Whirlwind(Warrior* pchar, WarriorSpells* spells);
    ~Whirlwind() override;

private:
    Warrior* warr;
    WarriorSpells* spells;

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;
};

#endif // WHIRLWIND_H
