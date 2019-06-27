#pragma once

#include "SharedDebuff.h"
#include "ItemModificationRequirer.h"
#include "TalentRequirer.h"

#include <QVector>

class Paladin;

class JudgementOfTheCrusader: public SharedDebuff, public TalentRequirer, public ItemModificationRequirer {
public:
    JudgementOfTheCrusader(Paladin* pchar);

private:
    unsigned libram_of_fervor_bonus {0};
    unsigned pvp_glove_bonus {0};
    double improved_sotc_mod {1.0};
    const unsigned holy_damage_base {140};
    const QVector<double> improved_sotc_ranks {1.0, 1.05, 1.10, 1.15};

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;

    void activate_item_effect(const int item_id) override;
    void deactivate_item_effect(const int item_id) override;
};
