#ifndef RESOURCEGAIN_H
#define RESOURCEGAIN_H

#include "Event.h"

class Spell;

class ResourceGain: public Event {
public:
    ResourceGain(Spell*, const float);

    virtual void act(void) override;
protected:
private:
    Spell* spell;
};

#endif // RESOURCEGAIN_H
