#pragma once

#include "CastingTimeRequirer.h"
#include "SetBonusRequirer.h"
#include "Spell.h"
#include "TalentRequirer.h"

class Hunter;
class StatisticsResource;

class AimedShot: public Spell, public CastingTimeRequirer, public TalentRequirer, public SetBonusRequirer {
public:
    AimedShot(Hunter* hunter, CooldownControl* cooldown_control);

private:
    Hunter* hunter;
    StatisticsResource* statistics_resource {nullptr};
    unsigned adrenaline_rush {0};
    double resource_base;
    double mortal_shots_bonus {0.0};
    const QVector<double> efficiency_ranks;
    const QVector<double> mortal_shots_ranks;

    void spell_effect() override;
    void complete_cast_effect() override;
    void prepare_set_of_combat_iterations_spell_specific() override;

    void add_adrenaline_rush_statistics();

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
    void activate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
    void deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
};
