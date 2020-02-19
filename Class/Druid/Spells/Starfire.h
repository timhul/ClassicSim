#pragma once

#include <QVector>

#include "CastingTimeRequirer.h"
#include "Spell.h"
#include "TalentRequirer.h"

class Druid;
class DruidSpells;
class Random;

class Starfire : public Spell, public CastingTimeRequirer, public TalentRequirer {
public:
    Starfire(Druid* pchar, DruidSpells* druid_spells, const int spell_rank);
    ~Starfire() override;

    bool is_rank_learned() const override;

private:
    DruidSpells* druid_spells;
    Random* instant_dmg;

    double spell_dmg_coefficient;
    unsigned base_resource_cost;
    unsigned base_damage_min;
    unsigned base_damage_max;

    const unsigned base_casting_time_ms;
    const QVector<unsigned> improved_starfire_ranks {0, 100, 200, 300, 400, 500};

    double vengeance_crit_damage_bonus {1.0};
    const QVector<double> vengeance_ranks {1.0, 1.2, 1.4, 1.6, 1.8, 2.0};

    const QVector<double> moonglow_ranks {1.0, 0.97, 0.94, 0.91};

    double moonfury_damage_bonus {1.0};
    const QVector<double> moonfury_ranks {1.0, 1.02, 1.04, 1.06, 1.08, 1.10};

    void spell_effect() override;
    void complete_cast_effect() override;

    void set_base_damage_range();

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
