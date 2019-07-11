#pragma once

#include "Event.h"

class SealOfCommand;

class SpellCallback: public Event {
public:
    SpellCallback(SealOfCommand* spell, const double timestamp);

    void act() override;

private:
    SealOfCommand* spell;
};
