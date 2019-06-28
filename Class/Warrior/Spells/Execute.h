#pragma once

#include "Spell.h"
#include "TalentRequirer.h"

class Warrior;
class WarriorSpells;

class Execute: public Spell, public TalentRequirer {
public:
    Execute(Warrior* pchar, WarriorSpells* spells);
    ~Execute() override;

private:
    Warrior* warr;
    WarriorSpells* spells;
    QVector<QPair<unsigned, unsigned>> spell_ranks;
    QVector<unsigned> talent_ranks;
    unsigned initial_dmg;
    unsigned dmg_per_rage_converted;
    double execute_threshold;

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
    void prepare_set_of_combat_iterations_spell_specific() override;
};
