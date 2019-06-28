#pragma once

#include "SetBonusRequirer.h"
#include "SpellCastingTime.h"
#include "TalentRequirer.h"

class Hunter;
class StatisticsResource;

class AimedShot: public SpellCastingTime, public TalentRequirer, public SetBonusRequirer {
public:
    AimedShot(Hunter* pchar, CooldownControl* cooldown_control);

private:
    Hunter* hunter;
    StatisticsResource* statistics_resource {nullptr};
    const unsigned base_casting_time_ms;
    unsigned adrenaline_rush {0};
    double resource_base;
    double mortal_shots_bonus;
    QVector<double> talent_ranks;
    QVector<double> efficiency_ranks;
    QVector<double> mortal_shots_ranks;

    void spell_effect() override;
    void complete_cast_effect() override;
    void prepare_set_of_combat_iterations_spell_specific() override;

    void add_adrenaline_rush_statistics();

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
    void activate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
    void deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
};
