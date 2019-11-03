#pragma once

#include "SetBonusRequirer.h"
#include "Spell.h"
#include "StatisticsResource.h"
#include "TalentRequirer.h"

class Rogue;

class Backstab: public Spell, public TalentRequirer, public SetBonusRequirer {
public:
    Backstab(Rogue* rogue);
    ~Backstab() override;

private:
    Rogue* rogue;
    StatisticsResource* statistics_resource {nullptr};
    unsigned improved_bs {0};
    double lethality {1.0};
    double opportunity {1.0};
    QVector<unsigned> imp_bs_ranks {0, 1000, 2000, 3000};
    QVector<double> lethality_ranks {1.0, 1.06, 1.12, 1.18, 1.24, 1.30};
    QVector<double> opportunity_ranks {1.0, 1.04, 1.08, 1.12, 1.16, 1.20};
    unsigned bonescythe_energy {0};

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
    void activate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
    void deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) override;

    void prepare_set_of_combat_iterations_spell_specific() override;
};
