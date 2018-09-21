#ifndef DOTTICK_H
#define DOTTICK_H

#include "Event.h"

class Spell;

class DotTick: public Event {
public:
    DotTick(Spell *spell, double priority);

    virtual void act(void) override;
protected:
private:
    Spell* spell;
};

#endif // DOTTICK_H
