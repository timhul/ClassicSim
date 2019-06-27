#pragma once

#include "Event.h"

class SpellCastingTime;

class CastComplete: public Event {
public:
    CastComplete(SpellCastingTime* spell, const double timestamp);

    void act() override;

private:
    SpellCastingTime* spell;
};
