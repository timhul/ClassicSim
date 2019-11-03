#pragma once

#include "Spell.h"

class Warrior;
class WarriorSpells;

class Recklessness: public Spell {
public:
    Recklessness(Warrior* warrior, WarriorSpells* spells);
    ~Recklessness() override;

private:
    Warrior* warrior;
    WarriorSpells* spells;

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;
};
