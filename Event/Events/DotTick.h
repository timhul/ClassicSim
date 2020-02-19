#pragma once

#include "Event.h"

class SpellPeriodic;

class DotTick : public Event {
public:
    DotTick(SpellPeriodic* spell, const double timestamp, const int application_id);

    void act() override;

private:
    SpellPeriodic* spell;

    const int application_id;
};
