#pragma once

#include "PeriodicResourceGainSpell.h"
#include "TalentRequirer.h"

class StatisticsResource;
class Warrior;

class Bloodrage: public PeriodicResourceGainSpell, public TalentRequirer {
public:
    Bloodrage(Warrior* warrior);

private:
    friend class ImprovedBloodrage;

    Warrior* warrior;

    QVector<unsigned> talent_ranks {10, 12, 15};
    unsigned immediate_rage_gain {10};
    const unsigned periodic_rage_base {10};
    unsigned periodic_rage_current {10};

    void new_application_effect() override;
    SpellStatus is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;

    void gain_rage(const unsigned rage_gain);
};
