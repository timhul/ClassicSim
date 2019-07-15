#pragma once

#include "Event.h"

class CastingTimeRequirer;

class CastComplete: public Event {
public:
    CastComplete(CastingTimeRequirer* cast, const double timestamp);

    void act() override;

private:
    CastingTimeRequirer* cast;
};
