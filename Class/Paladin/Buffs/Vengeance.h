#pragma once

#include <QVector>

#include "SelfBuff.h"
#include "TalentRequirer.h"

class Paladin;

class Vengeance : public SelfBuff, public TalentRequirer {
public:
    Vengeance(Paladin* paladin);
    ~Vengeance() override = default;

private:
    Paladin* paladin;

    unsigned dmg_bonus {0};
    const QVector<unsigned> dmg_bonuses;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
