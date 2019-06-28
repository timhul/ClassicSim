#pragma once

#include "Spell.h"
#include "TalentRequirer.h"

class Warrior;
class WarriorSpells;

class Overpower: public Spell, public TalentRequirer {
public:
    Overpower(Warrior* pchar, WarriorSpells* spells, CooldownControl* cooldown_control);

private:
    Warrior* warr;
    WarriorSpells* spells;
    QVector<unsigned> talent_ranks;
    unsigned crit_mod;

    SpellStatus is_ready_spell_specific() const override;
    void spell_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
