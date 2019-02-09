#ifndef SEALFATE_H
#define SEALFATE_H

#include "Proc.h"
#include "TalentRequirer.h"

class Rogue;

class SealFate: public Proc, public TalentRequirer {
public:
    SealFate(Character* pchar);
    ~SealFate() override;

    void proc_effect() override;

private:
    Rogue* rogue;
    QVector<unsigned> talent_ranks;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // SEALFATE_H
