#pragma once

#include "Proc.h"
#include "TalentRequirer.h"

class StatisticsResource;
class Warrior;

class UnbridledWrath: public Proc, public TalentRequirer {
public:
    UnbridledWrath(Character* pchar);

    void proc_effect() override;

private:
    StatisticsResource* statistics_resource;
    Warrior* warr;
    const QVector<unsigned> talent_ranks;

    void prepare_set_of_combat_iterations_spell_specific() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
