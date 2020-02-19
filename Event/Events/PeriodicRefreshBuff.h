#pragma once

#include "Event.h"

class Buff;

class PeriodicRefreshBuff : public Event {
public:
    PeriodicRefreshBuff(Buff* buff, const double timestamp);

    void act() override;

private:
    Buff* buff;
};
