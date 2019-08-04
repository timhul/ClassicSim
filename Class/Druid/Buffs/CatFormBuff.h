#pragma once

#include "SelfBuff.h"
#include "TalentRequirer.h"

#include <QVector>

class Druid;

class CatFormBuff: public SelfBuff, public TalentRequirer {
public:
    CatFormBuff(Druid* pchar);

private:
    Druid* druid;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

    unsigned sharpened_claws_bonus {0};
    const QVector<unsigned> sharpened_claws_ranks {0, 200, 400, 600};

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
