#ifndef SEALOFTHECRUSADER_H
#define SEALOFTHECRUSADER_H

#include "PaladinSeal.h"
#include "TalentRequirer.h"

class Paladin;
class SealOfTheCrusaderBuff;

class SealOfTheCrusader: public PaladinSeal, public TalentRequirer {
public:
    SealOfTheCrusader(Paladin* pchar);

private:
    const int base_mana_cost {160};
    const QVector<double> benediction_ranks {1.0, 0.97, 0.94, 0.91, 0.88, 0.85};

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // SEALOFTHECRUSADER_H
