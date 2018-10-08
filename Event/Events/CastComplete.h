#ifndef CASTCOMPLETE_H
#define CASTCOMPLETE_H

#include "Event.h"

class Spell;

class CastComplete: public Event {
public:
    CastComplete(Spell*, const double);

    virtual void act(void) override;
protected:
private:
    Spell* spell;
};

#endif // CASTCOMPLETE_H
