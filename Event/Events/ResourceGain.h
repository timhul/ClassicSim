#pragma once

#include "Event.h"

class Spell;

class ResourceGain: public Event {
public:
    ResourceGain(Spell* spell, const double timestamp);

    void act() override;

private:
    Spell* spell;
};
