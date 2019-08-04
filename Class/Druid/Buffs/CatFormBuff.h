#pragma once

#include "SelfBuff.h"
#include "TalentRequirer.h"

#include <QVector>

class Buff;
class Druid;

class CatFormBuff: public SelfBuff, public TalentRequirer {
public:
    CatFormBuff(Druid* pchar, Buff* leader_of_the_pack, Proc* furor);

private:
    Druid* druid;
    Buff* leader_of_the_pack;
    Proc* furor;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

    unsigned sharpened_claws_bonus {0};
    const QVector<unsigned> sharpened_claws_ranks {0, 200, 400, 600};

    unsigned predatory_strikes_bonus {0};
    const QVector<double> predatory_strikes_ranks {0, 0.5, 1.0, 1.5};

    int heart_of_the_wild_mod {0};
    const QVector<int> heart_of_the_wild_str_mod_ranks {0, 4, 8, 12, 16, 20};

    bool supplies_leader_of_the_pack {false};

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};
