#pragma once

#include "CastingTimeRequirer.h"
#include "Spell.h"
#include "TalentRequirer.h"

#include <QVector>

class Druid;
class DruidSpells;
class Random;

class Starfire: public Spell, public CastingTimeRequirer, public TalentRequirer {
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

    void spell_effect() override;
    void complete_cast_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
