#ifndef SEALOFTHECRUSADERBUFF_H
#define SEALOFTHECRUSADERBUFF_H

#include "SelfBuff.h"
#include "ItemModificationRequirer.h"
#include "TalentRequirer.h"

#include <QVector>

class Paladin;

class SealOfTheCrusaderBuff: public SelfBuff, public TalentRequirer, public ItemModificationRequirer {
public:
    SealOfTheCrusaderBuff(Paladin* pchar);
    ~SealOfTheCrusaderBuff() override = default;

private:
    Paladin* paladin;

    unsigned libram_of_fervor_bonus {0};
    double improved_sotc_mod {1.0};
    const unsigned sotc_ap_base {306};
    const QVector<double> improved_sotc_ranks {1.0, 1.05, 1.10, 1.15};

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;

    void activate_item_effect(const int item_id) override;
    void deactivate_item_effect(const int item_id) override;
};

#endif // SEALOFTHECRUSADERBUFF_H
