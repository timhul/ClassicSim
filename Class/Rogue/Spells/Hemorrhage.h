#pragma once

#include "SetBonusRequirer.h"
#include "Spell.h"
#include "StatisticsResource.h"
#include "TalentRequirer.h"

class Rogue;

class Hemorrhage: public Spell, public TalentRequirer, public SetBonusRequirer {
public:
    Hemorrhage(Character* pchar);
    ~Hemorrhage() override;

private:
    Rogue* rogue;
    StatisticsResource* statistics_resource;
    double lethality {1.0};
    const QVector<double> lethality_ranks;
    unsigned bonescythe_energy {0};

    void spell_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
    void activate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
    void deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) override;

    void prepare_set_of_combat_iterations_spell_specific() override;
};
