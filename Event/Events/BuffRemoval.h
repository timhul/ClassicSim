#pragma once

#include "Event.h"

class Buff;

class BuffRemoval : public Event {
public:
    BuffRemoval(Buff* buff, const double timestamp, const int iteration);

    void act() override;

private:
    Buff* buff;
    const int iteration;
};
