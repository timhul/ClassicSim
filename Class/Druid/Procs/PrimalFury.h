#pragma once

#include "Proc.h"
#include "TalentRequirer.h"

class Druid;

class PrimalFury : public Proc, public TalentRequirer {
public:
    PrimalFury(Druid* druid);
    void proc_effect() override;

private:
    Druid* druid;
    const QVector<unsigned> talent_ranks;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
