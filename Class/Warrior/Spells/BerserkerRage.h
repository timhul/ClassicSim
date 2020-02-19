#pragma once

#include "Spell.h"
#include "TalentRequirer.h"

class StatisticsResource;
class Warrior;

class BerserkerRage : public Spell, public TalentRequirer {
public:
    BerserkerRage(Warrior* warrior);
    ~BerserkerRage() override;

private:
    Warrior* warrior;
    StatisticsResource* statistics_resource;
    const QVector<unsigned> talent_ranks;
    unsigned rage_gain {0};

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;

    void prepare_set_of_combat_iterations_spell_specific() override;
};
