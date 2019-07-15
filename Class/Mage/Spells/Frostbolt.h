#pragma once

#include "CastingTimeRequirer.h"
#include "Spell.h"
#include "TalentRequirer.h"

#include <QVector>

class Buff;
class Mage;
class MageSpells;
class Random;
class StatisticsResource;

class Frostbolt: public Spell, public CastingTimeRequirer, public TalentRequirer {
public:
    Frostbolt(Mage* pchar, MageSpells* mage_spells, const int spell_rank);
    ~Frostbolt() override;

    bool is_rank_learned() const override;

private:
    MageSpells* mage_spells;
    Random* instant_dmg;
    StatisticsResource* statistics_resource {nullptr};

    double spell_dmg_coefficient;
    unsigned base_resource_cost;
    unsigned base_damage_min;
    unsigned base_damage_max;

    unsigned base_casting_time_ms;
    const QVector<unsigned> improved_frostbolt_ranks {0, 100, 200, 300, 400, 500};

    double master_of_elements_mana_return {0.0};
    const QVector<double> master_of_elements_ranks {0.0, 0.1, 0.2, 0.3};

    double ice_shards_multiplier {1.0};
    const QVector<double> ice_shards_ranks {1.0, 1.2, 1.4, 1.6, 1.8, 2.0};
    double spell_crit_dmg_mod {1.5};

    const QVector<double> frost_channeling_ranks {1.0, 0.95, 0.90, 0.85};

    void gain_mana(const double mana_gain);

    void spell_effect() override;
    void complete_cast_effect() override;
    void prepare_set_of_combat_iterations_spell_specific() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
