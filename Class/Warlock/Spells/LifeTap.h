#pragma once

#include <QVector>

#include "Spell.h"
#include "TalentRequirer.h"

class StatisticsResource;
class Warlock;
class WarlockSpells;

class LifeTap : public Spell, public TalentRequirer {
public:
    LifeTap(Warlock* warlock, WarlockSpells* warlock_spells, const int spell_rank_);
    ~LifeTap() override;

    bool is_rank_learned() const override;

private:
    WarlockSpells* warlock_spells;
    StatisticsResource* statistics_resource {nullptr};

    const double spell_dmg_coefficient {0.8};
    unsigned base_resource_yield;
    unsigned resource_yield;

    double imp_life_tap {1.0};
    const QVector<double> imp_life_tap_ranks {1.0, 1.1, 1.2};

    void spell_effect() override;
    void prepare_set_of_combat_iterations_spell_specific() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
