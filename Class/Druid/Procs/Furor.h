#pragma once

#include "Proc.h"
#include "TalentRequirer.h"

#include <QVector>

class Druid;
class StatisticsResource;

class Furor: public Proc, public TalentRequirer {
public:
    Furor(Character* pchar);

    void proc_effect() override;

private:
    StatisticsResource* statistics_resource;
    Druid* druid;

    const QVector<unsigned> talent_ranks {0, 2000, 4000, 6000, 8000, 10000};

    void prepare_set_of_combat_iterations_spell_specific() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
