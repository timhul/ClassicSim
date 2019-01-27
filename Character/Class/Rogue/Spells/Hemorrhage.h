#ifndef HEMORRHAGE_H
#define HEMORRHAGE_H

#include "SetBonusRequirer.h"
#include "Spell.h"
#include "StatisticsResource.h"
#include "TalentRequirer.h"

class Rogue;

class Hemorrhage: public Spell, public TalentRequirer, public SetBonusRequirer {
public:
    Hemorrhage(Character* pchar);

private:
    friend class HemorrhageTalent;

    Rogue* rogue;
    StatisticsResource* statistics_resource;
    double lethality;
    QVector<double> lethality_ranks;
    unsigned bonescythe_energy;

    void spell_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
    void activate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
    void deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) override;

    void prepare_set_of_combat_iterations_spell_specific() override;
};

#endif // HEMORRHAGE_H
