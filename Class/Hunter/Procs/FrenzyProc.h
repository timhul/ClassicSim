#pragma once

#include "Proc.h"
#include "TalentRequirer.h"

class FrenzyBuff;
class Pet;

class FrenzyProc: public Proc, public TalentRequirer {
public:
    FrenzyProc(Character* pchar, Pet* pet);
    ~FrenzyProc() override;

private:
    FrenzyBuff* frenzy_buff;
    QVector<unsigned> talent_ranks;

    void proc_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
