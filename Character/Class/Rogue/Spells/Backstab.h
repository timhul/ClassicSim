#ifndef BACKSTAB_H
#define BACKSTAB_H

#include "SetBonusRequirer.h"
#include "Spell.h"
#include "StatisticsResource.h"
#include "TalentRequirer.h"

class Rogue;

class Backstab: public Spell, public TalentRequirer, public SetBonusRequirer {
public:
    Backstab(Character* pchar);

private:
    friend class Opportunity;

    Rogue* rogue;
    StatisticsResource* statistics_resource;
    double improved_bs;
    double lethality;
    double opportunity;
    QVector<double> imp_bs_ranks;
    QVector<double> lethality_ranks;
    QVector<double> opportunity_ranks;
    unsigned bonescythe_energy;

    void spell_effect() override;
    bool is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
    void activate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
    void deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) override;

    void prepare_set_of_combat_iterations_spell_specific() override;
};

#endif // BACKSTAB_H
