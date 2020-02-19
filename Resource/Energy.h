#pragma once

#include "RegeneratingResource.h"

class Character;

class Energy : public RegeneratingResource {
public:
    Energy(Character*);

    unsigned get_max_resource() const override;
    unsigned get_resource_per_tick() override;
    ResourceType get_resource_type() const override;
    double get_tick_rate() const override;

    void increase_energy_per_tick();
    void decrease_energy_per_tick();

    friend class Druid;
    friend class Rogue;
    friend class SetBonusControl;
    friend class Vigor;

private:
    void reset_effect() override;
    void lose_resource_effect() override;

    unsigned energy_per_tick;
    unsigned max_energy_bonus;
};
