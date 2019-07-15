#pragma once

#include "CastingTimeRequirer.h"
#include "Spell.h"
#include "TalentRequirer.h"

#include <QVector>

class Buff;
class FireballInstant;
class Mage;
class MageSpells;
class StatisticsResource;

class Fireball: public Spell, public CastingTimeRequirer, public TalentRequirer {
public:
    Fireball(Mage* pchar, MageSpells* mage_spells, const int spell_rank);
    ~Fireball() override;

    bool is_rank_learned() const override;
    void prepare_set_of_combat_iterations() override;

private:
    MageSpells* mage_spells;
    FireballInstant* damage_spell;
    StatisticsResource* statistics_resource {nullptr};

    double spell_dmg_coefficient;
    unsigned base_resource_cost;
    unsigned base_damage_min;
    unsigned base_damage_max;
    unsigned base_dot_damage;
    int base_dot_duration;

    unsigned base_casting_time_ms;
    QVector<unsigned> improved_fireball_ranks {0, 100, 200, 300, 400, 500};

    double master_of_elements_mana_return {0.0};
    QVector<double> master_of_elements_ranks {0.0, 0.1, 0.2, 0.3};
    QVector<unsigned> critical_mass_ranks {0, 200, 400, 600};

    void gain_mana(const double mana_gain);

    void spell_effect() override;
    void complete_cast_effect() override;
    void prepare_set_of_combat_iterations_spell_specific() override;
    void reset_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
