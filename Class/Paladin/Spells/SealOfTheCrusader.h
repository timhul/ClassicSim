#pragma once

#include "ItemModificationRequirer.h"
#include "PaladinSeal.h"
#include "TalentRequirer.h"

class JudgementOfTheCrusader;
class Paladin;
class SealOfTheCrusaderBuff;

class SealOfTheCrusader : public PaladinSeal, public TalentRequirer, public ItemModificationRequirer {
public:
    SealOfTheCrusader(Paladin* pchar, JudgementOfTheCrusader* judge_debuff);
    ~SealOfTheCrusader() override;

    void refresh_seal() const override;
    Buff* get_judge_debuff() const;

private:
    const int base_mana_cost {160};
    const QVector<double> benediction_ranks {1.0, 0.97, 0.94, 0.91, 0.88, 0.85};

    void judge_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;

    void activate_item_effect(const int item_id) override;
    void deactivate_item_effect(const int item_id) override;
};
