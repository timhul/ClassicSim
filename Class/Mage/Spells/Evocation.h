#pragma once

#include "CastingTimeRequirer.h"
#include "SetBonusRequirer.h"
#include "SpellPeriodic.h"

class Mage;

class Evocation : public SpellPeriodic, public CastingTimeRequirer, public SetBonusRequirer {
public:
    Evocation(Mage* mage);
    ~Evocation() override;

private:
    void complete_cast_effect() override;

    bool check_application_success() override;
    void new_application_effect() override;
    void refresh_effect() override;
    void reset_effect() override;
    void tick_effect() override;

    void activate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
    void deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
};
