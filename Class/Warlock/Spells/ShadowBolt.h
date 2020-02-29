#pragma once

#include <QVector>

#include "CastingTimeRequirer.h"
#include "Spell.h"
#include "TalentRequirer.h"

class ImprovedShadowBolt;
class Random;
class Warlock;
class WarlockSpells;

class ShadowBolt : public Spell, public CastingTimeRequirer, public TalentRequirer {
public:
    ShadowBolt(Warlock* warlock, WarlockSpells* warlock_spells, const int spell_rank_, ImprovedShadowBolt* imp_sb);
    ~ShadowBolt() override;

    bool is_rank_learned() const override;

private:
    ImprovedShadowBolt* imp_sb;
    WarlockSpells* warlock_spells;
    Random* instant_dmg;

    double spell_dmg_coefficient;
    unsigned base_casting_time_ms;
    unsigned base_resource_cost;
    unsigned base_damage_min;
    unsigned base_damage_max;

    const QVector<double> cataclysm_ranks {1.0, 0.99, 0.98, 0.97, 0.96, 0.95};
    const QVector<unsigned> bane_ranks {0, 100, 200, 300, 400, 500};
    unsigned devastation_bonus {0};
    const QVector<unsigned> devastation_ranks {0, 100, 200, 300, 400, 500};
    double ruin_crit_damage_bonus {1.0};
    bool apply_imp_sb {false};

    void spell_effect() override;
    void complete_cast_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
