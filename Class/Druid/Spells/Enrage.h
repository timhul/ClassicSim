#pragma once

#include "PeriodicResourceGainSpell.h"
#include "TalentRequirer.h"

class Druid;

class Enrage : public PeriodicResourceGainSpell, public TalentRequirer {
public:
    Enrage(Druid* druid);

private:
    friend class ImprovedEnrage;

    Druid* drood;

    QVector<unsigned> talent_ranks {0, 5, 10};
    unsigned immediate_rage_gain {0};
    const unsigned periodic_rage_base {20};
    unsigned periodic_rage_current {20};

    void new_application_effect() override;
    SpellStatus is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;

    void gain_rage(const unsigned rage_gain);
};
