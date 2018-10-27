#ifndef PERIODICAPPLYBUFF_H
#define PERIODICAPPLYBUFF_H

#include "Event.h"

class Buff;
class Character;


class PeriodicRefreshBuff: public Event {
public:
    PeriodicRefreshBuff(Character*, Buff*, const double);

    virtual void act(void) override;
protected:
private:
    Character* pchar;
    Buff* buff;
};

#endif // PERIODICAPPLYBUFF_H
