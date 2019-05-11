#ifndef BLOODTHIRST_H
#define BLOODTHIRST_H

#include "Spell.h"
#include "TalentRequirer.h"

class Warrior;
class WarriorSpells;

class Bloodthirst: public Spell, public TalentRequirer {
public:
    Bloodthirst(Warrior* pchar, WarriorSpells* spells);

private:
    Warrior* warr;
    WarriorSpells* spells;

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // BLOODTHIRST_H
