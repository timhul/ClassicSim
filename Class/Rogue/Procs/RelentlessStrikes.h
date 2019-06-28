#pragma once

#include "Proc.h"
#include "TalentRequirer.h"

class Rogue;
class StatisticsResource;

class RelentlessStrikes: public Proc, public TalentRequirer {
public:
    RelentlessStrikes(Character* pchar);
    ~RelentlessStrikes() override;

    void proc_effect() override;
    void set_current_combo_points(const unsigned);

private:
    StatisticsResource* statistics_resource;
    Rogue* rogue;
    unsigned combo_proc_percent;
    QVector<unsigned> talent_ranks;

    void prepare_set_of_combat_iterations_spell_specific() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
