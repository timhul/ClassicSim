#pragma once

#include <QVector>

#include "CastingTimeRequirer.h"
#include "Spell.h"
#include "TalentRequirer.h"

class Buff;
class Mage;
class Random;
class MageSpells;
class StatisticsResource;

class Scorch : public Spell, public CastingTimeRequirer, public TalentRequirer {
public:
    Scorch(Mage* pchar, MageSpells* mage_spells, Proc* proc, const int spell_rank);
    ~Scorch() override;

    bool is_rank_learned() const override;

private:
    MageSpells* mage_spells;
    StatisticsResource* statistics_resource {nullptr};
    Random* instant_dmg;
    Proc* imp_scorch;

    double spell_dmg_coefficient;
    unsigned base_resource_cost;
    unsigned base_damage_min;
    unsigned base_damage_max;

    unsigned incinerate {0};
    QVector<unsigned> incinerate_ranks {0, 200, 400};
    double master_of_elements_mana_return {0.0};
    QVector<double> master_of_elements_ranks {0.0, 0.1, 0.2, 0.3};
    unsigned imp_critical_mass {0};
    QVector<unsigned> critical_mass_ranks {0, 200, 400, 600};

    void gain_mana(const double mana_gain);

    void spell_effect() override;
    void complete_cast_effect() override;
    void prepare_set_of_combat_iterations_spell_specific() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
