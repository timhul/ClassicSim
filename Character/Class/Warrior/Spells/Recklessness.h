#ifndef RECKLESSNESS_H
#define RECKLESSNESS_H

#include "Spell.h"

class Warrior;
class WarriorSpells;

class Recklessness: public Spell {
public:
    Recklessness(Warrior* pchar, WarriorSpells* spells);

private:
    WarriorSpells* spells;

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;
};

#endif // RECKLESSNESS_H
