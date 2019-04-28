#ifndef SEALOFTHECRUSADER_H
#define SEALOFTHECRUSADER_H

#include "PaladinSeal.h"
#include "TalentRequirer.h"

class Paladin;
class SealOfTheCrusaderBuff;

class SealOfTheCrusader: public PaladinSeal, public TalentRequirer {
public:
    SealOfTheCrusader(Paladin* pchar);
    ~SealOfTheCrusader() override;

    void refresh_seal() const override;
    Buff* get_judge_debuff() const;

private:
    Buff* judge_debuff;

    const int base_mana_cost {160};
    const QVector<double> benediction_ranks {1.0, 0.97, 0.94, 0.91, 0.88, 0.85};

    void judge_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // SEALOFTHECRUSADER_H
