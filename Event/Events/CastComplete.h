#ifndef CASTCOMPLETE_H
#define CASTCOMPLETE_H

#include "Event.h"

class SpellCastingTime;

class CastComplete: public Event {
public:
    CastComplete(SpellCastingTime* spell, const double timestamp);

    void act() override;

private:
    SpellCastingTime* spell;
};

#endif // CASTCOMPLETE_H
