#pragma once

#include "Spell.h"
#include "TalentRequirer.h"

class Paladin;
class PaladinSpells;

class Judgement: public Spell, public TalentRequirer {
public:
    Judgement(Paladin* paladin, PaladinSpells* paladin_spells, CooldownControl* cooldown_control);

private:
    Paladin* paladin;
    PaladinSpells* paladin_spells;

    const double base_mana_cost { 1436 * 0.06 };
    const QVector<double> benediction_ranks {1.0, 0.97, 0.94, 0.91, 0.88, 0.85};

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
