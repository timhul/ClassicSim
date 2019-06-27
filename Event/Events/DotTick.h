#pragma once

#include "Event.h"

class Spell;

class DotTick: public Event {
public:
    DotTick(Spell* spell, const double timestamp);

    void act() override;

private:
    Spell* spell;
};
