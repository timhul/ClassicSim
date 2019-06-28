#pragma once

#include "Proc.h"
#include "TalentRequirer.h"

class Rogue;

class Ruthlessness: public Proc, public TalentRequirer {
public:
    Ruthlessness(Character* pchar);
    ~Ruthlessness() override;

    void proc_effect() override;

private:
    Rogue* rogue;
    QVector<unsigned> talent_ranks;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
