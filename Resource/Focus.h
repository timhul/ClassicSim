#pragma once

#include "RegeneratingResource.h"

class Character;

class Focus : public RegeneratingResource {
public:
    Focus(Character*);

    friend class HunterPet;
    friend class TalentStatIncrease;

    unsigned get_max_resource() const override;
    unsigned get_resource_per_tick() override;
    ResourceType get_resource_type() const override;
    double get_tick_rate() const override;

private:
    unsigned focus_gain;
    void reset_effect() override;
    void lose_resource_effect() override;

    void increase_focus_gain();
    void decrease_focus_gain();
};
