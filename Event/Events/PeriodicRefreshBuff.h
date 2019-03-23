#ifndef PERIODICREFRESHBUFF_H
#define PERIODICREFRESHBUFF_H

#include "Event.h"

class Buff;
class Character;

class PeriodicRefreshBuff: public Event {
public:
    PeriodicRefreshBuff(Character* pchar, Buff* buff, const double timestamp);

    void act() override;

private:
    Character* pchar;
    Buff* buff;
};

#endif // PERIODICREFRESHBUFF_H
