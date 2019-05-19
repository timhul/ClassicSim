#ifndef MORTALSTRIKE_H
#define MORTALSTRIKE_H

#include "Spell.h"
#include "TalentRequirer.h"

class Warrior;
class WarriorSpells;

class MortalStrike: public Spell, public TalentRequirer {
public:
    MortalStrike(Warrior* pchar, WarriorSpells* spells, CooldownControl* cooldown_control);

private:
    Warrior* warr;
    WarriorSpells* spells;

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // MORTALSTRIKE_H
