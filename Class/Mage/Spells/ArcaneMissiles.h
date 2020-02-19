#pragma once

#include "CastingTimeRequirer.h"
#include "SpellPeriodic.h"

class MageSpells;

class ArcaneMissiles : public SpellPeriodic, public CastingTimeRequirer {
public:
    ArcaneMissiles(Character* pchar, MageSpells* spells, const int spell_rank);
    ~ArcaneMissiles() override;

    bool is_rank_learned() const override;

private:
    MageSpells* mage_spells;

    unsigned damage_per_missile;

    void complete_cast_effect() override;

    bool check_application_success() override;
    void new_application_effect() override;
    void refresh_effect() override;
    void reset_effect() override;
    void tick_effect() override;
};
