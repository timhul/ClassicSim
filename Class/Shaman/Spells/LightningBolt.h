#pragma once

#include "SpellCastingTime.h"
#include "TalentRequirer.h"

#include <QVector>

class Buff;
class Shaman;
class Random;

class LightningBolt: public SpellCastingTime, public TalentRequirer {
public:
    LightningBolt(Shaman* pchar, const int spell_rank);
    ~LightningBolt() override;

    bool is_rank_learned() const override;

private:
    Random* random;
    unsigned base_damage_min;
    unsigned base_damage_max;
    unsigned base_resource_cost;
    double spell_dmg_coefficient;
    unsigned tidal_mastery_mod {0};
    QVector<unsigned> tidal_mastery_ranks {0, 100, 200, 300, 400, 500};
    unsigned call_of_thunder_mod {0};
    QVector<unsigned> call_of_thunder_ranks {0, 100, 200, 300, 400, 600};
    double concussion_mod {1.0};
    QVector<double> concussion_ranks {1.0, 1.01, 1.02, 1.03, 1.04, 1.05};
    QVector<double> convection_ranks {1.0, 0.98, 0.96, 0.94, 0.92, 0.90};
    const unsigned lightning_mastery_mod {200};

    void spell_effect() override;
    void complete_cast_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
