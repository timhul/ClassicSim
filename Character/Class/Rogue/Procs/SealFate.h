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

protected:
private:
    friend class SealFateTalent;

    Rogue* rogue;

    void increase_talent_rank_effect(const int curr, const QString& talent_name) override;
    void decrease_talent_rank_effect(const int curr, const QString& talent_name) override;
};

#endif // SEALFATE_H
