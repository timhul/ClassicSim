#pragma once

#include "CastingTimeRequirer.h"
#include "SpellPeriodic.h"

class Evocation: public SpellPeriodic, public CastingTimeRequirer {
public:
    Evocation(Character* pchar);
    ~Evocation() override;

private:
    void complete_cast_effect() override;

    bool check_application_success() override;
    void new_application_effect() override;
    void refresh_effect() override;
    void reset_effect() override;
    void tick_effect() override;
};
