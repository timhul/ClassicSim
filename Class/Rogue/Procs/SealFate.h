#pragma once

#include "Proc.h"
#include "TalentRequirer.h"

class Rogue;

class SealFate: public Proc, public TalentRequirer {
public:
    SealFate(Rogue* rogue);

    void proc_effect() override;

private:
    Rogue* rogue;
    const QVector<unsigned> talent_ranks;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
