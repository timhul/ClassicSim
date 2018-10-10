#ifndef CASTCOMPLETE_H
#define CASTCOMPLETE_H

#include "Event.h"

class SpellCastingTime;

class CastComplete: public Event {
public:
    CastComplete(SpellCastingTime *, const double);

    virtual void act(void) override;
protected:
private:
    SpellCastingTime* spell;
};

#endif // CASTCOMPLETE_H
