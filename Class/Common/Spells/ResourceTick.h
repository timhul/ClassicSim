#pragma once

#include "SpellPeriodic.h"

class RegeneratingResource;

class ResourceTick : public SpellPeriodic {
public:
    ResourceTick(Character* pchar, RegeneratingResource* resource);
    ~ResourceTick() override;

private:
    RegeneratingResource* resource;

    bool check_application_success() override;
    void new_application_effect() override;
    void refresh_effect() override;
    void tick_effect() override;
    void reset_effect() override;
};
